#include "main.hpp"

// Ignore Windows getenv warning bullshit
// #define _CRT_SECURE_NO_WARNINGS
// #pragma warning(disable:4996)

#include <filesystem>
#include <string>
#include <toml.hpp>

#include "commands/install.hpp"
#include "commands/remove.hpp"
#include "commands/search.hpp"
#include "commands/update.hpp"
#include "utils/platform.hpp"

int main(int argc, char *argv[]) { Cli cli(argc, argv); }

Cli::Cli(int argc, char *argv[]) {
  if (!ReadArguments(argc, argv)) {
    PrintUsage();
    return;
  }
  if (!Platform::IsElevated()) {
    if (noRoot) {
      if (!quiet)
        std::cout << "Attention the current user does not have administrator "
                     "permission."
                  << std::endl;
    } else {
      std::cout << "Error, current user does not have administrator permission."
                << std::endl;
      return;
    }
  }
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
  configPath = "C:\\ProgramData\\owopkg\\config.toml";
  repoPath = "C:\\ProgramData\\owopkg\\repo";
  databasePath = "C:\\ProgramData\\owopkg";
  cachePath = std::filesystem::temp_directory_path() / "owopkg";
#elif __APPLE__
  configPath = "/Library/Preferences/owopkg/config.toml";
  repoPath = "/Library/Preferences/owopkg/repo";
  databasePath = "/Library/Application Support/owopkg";
  cachePath = "/Library/Caches/owopkg";
#elif __linux__ || __unix__
  configPath = "/etc/owopkg/config.toml";
  repoPath = "/etc/owopkg/repo";
  databasePath = "/var/lib/owopkg";
  cachePath = "/var/cache/owopkg";
#endif
  try {
    if (std::filesystem::exists(configPath)) {
      const auto config = toml::parse(configPath);
      if (config.contains("repo_path"))
        repoPath = toml::find<std::string>(config, "repo_path");
      if (config.contains("cache_path"))
        cachePath = toml::find<std::string>(config, "cache_path");
      if (config.contains("database_path"))
        databasePath = toml::find<std::string>(config, "database_path");
    }
  } catch (std::exception &ex) {
    std::cout << "Failed to read config at " << configPath << std::endl;
    std::cout << ex.what() << std::endl;
    return;
  }
  try {
    if (const char *owoRepo = std::getenv("OWOCONFIG"))
      repoPath = std::string(owoRepo);
    if (const char *owoDb = std::getenv("OWODB"))
      databasePath = std::string(owoDb);
    if (const char *owoCache = std::getenv("OWOCACHE"))
      cachePath = std::string(owoCache);
    EnsurePaths();
    owopkg = new OwOPkg(repoPath, cachePath, databasePath);
    owopkg->RegisterAppender(this);
    owopkg->Init();
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
    return;
  }
  try {
    ProcessCommand();
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
  }
}

Cli::~Cli() {
  if (owopkg != nullptr)
    delete owopkg;
}

bool Cli::ReadArguments(int argc, char *argv[]) {
  std::vector<std::string> rawPackages;

  auto installCmd =
      (clipp::command("install").set(selectedCmd, Command::install),
       clipp::values("packages", rawPackages));
  auto updateCmd = (clipp::command("update").set(selectedCmd, Command::update),
                    clipp::opt_values("packages", rawPackages));
  auto searchCmd = (clipp::command("search").set(selectedCmd, Command::search),
                    clipp::values("packages", rawPackages));
  auto removeCmd = (clipp::command("remove").set(selectedCmd, Command::remove),
                    clipp::values("packages", rawPackages));
  auto helpCmd = (clipp::command("help").set(selectedCmd, Command::help));
  auto forceOpt = (clipp::option("--force", "-f").set(force, true));
  auto quietOpt = (clipp::option("--quiet", "-q").set(quiet, true));
  auto verboseOpt = (clipp::option("--verbose", "-v").set(verbose, true));
  auto noRootOpt = (clipp::option("--noroot", "-nr").set(noRoot, true));

  auto clippParameters =
      (installCmd | updateCmd | searchCmd | removeCmd | helpCmd, forceOpt,
       quietOpt, verboseOpt, noRootOpt);

  if (parse(argc, argv, clippParameters)) {
    std::set<std::string> packages;
    for (const auto &pkg : rawPackages) {
      packages.insert(pkg);
    }
    return true;
  }
  return false;
}

void Cli::ProcessCommand() {
  switch (selectedCmd) {
  case Command::install:
    owo::commands::install(this, packages);
    break;
  case Command::update:
    owo::commands::update(this, packages);
    break;
  case Command::search:
    owo::commands::search(this, packages);
    break;
  case Command::remove:
    owo::commands::remove(this, packages);
    break;
  case Command::help:
    PrintUsage();
    break;
  }
}

void CreateDirectory(std::filesystem::path path) {
  if (!std::filesystem::is_directory(path) && !std::filesystem::exists(path)) {
    std::error_code ec;
    if (!std::filesystem::create_directory(path, ec)) {
      std::cout << ec.message() << std::endl;
      throw std::runtime_error("Failed to create directory " + path.string());
    }
  }
}

void Cli::EnsurePaths() {
  CreateDirectory(repoPath);
  CreateDirectory(databasePath);
  CreateDirectory(cachePath);
}

void Cli::PrintUsage() {
  std::cout << "owo-pkg v1.0.0\n";
  std::cout << "Usage: owo [options] command\n\n";
  std::cout
      << "owo-pkg is a private package manager for installing packages.\n\n";
  std::cout << "Commands:\n";
  std::cout << "  install <packages>\n";
  std::cout << "  update <packages>\n";
  std::cout << "  search <packages>\n";
  std::cout << "  remove <packages>";
  std::cout << std::endl;
}

void Cli::OnLog(owo::core::LogType type, std::string message) {
  if (quiet && type < owo::core::LogType::Error)
    return;
  if (!verbose && type == owo::core::LogType::Verbose)
    return;
  std::cout << message << std::endl;
}
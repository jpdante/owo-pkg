#include "cli.hpp"

#include <set>
#include <toml.hpp>

#include "commands/install.hpp"
#include "commands/remove.hpp"
#include "commands/search.hpp"
#include "commands/update.hpp"

namespace owo {

void setup_cli(int argc, char* argv[]) {
  enum class mode { install, update, search, remove, help };

  std::string defaultConfigPath = "../tmp/config.toml";

  Config config = load_config(defaultConfigPath);
  mode selected = mode::help;
  std::vector<std::string> rawPackages;
  bool verbose = false;
  bool force = false;

  auto installMode = (clipp::command("install").set(selected, mode::install),
                      clipp::values("packages", rawPackages));

  auto updateMode = (clipp::command("update").set(selected, mode::update),
                     clipp::opt_values("packages", rawPackages));

  auto searchMode = (clipp::command("search").set(selected, mode::search),
                     clipp::opt_values("packages", rawPackages));

  auto removeMode = (clipp::command("remove").set(selected, mode::remove),
                     clipp::values("packages", rawPackages));

  auto cli = (installMode | updateMode | searchMode | removeMode |
                  clipp::command("help").set(selected, mode::help),
              clipp::option("--verbose", "-v").set(verbose, true),
              clipp::option("--force", "-f").set(force, true));

  if (parse(argc, argv, cli)) {
    std::set<std::string> packages;
    for (const auto& pkg : rawPackages) {
      packages.insert(pkg);
    }
    switch (selected) {
      case mode::install:
        cmd::install(config, packages, verbose, force);
        break;
      case mode::update:
        cmd::update(config, packages, verbose, force);
        break;
      case mode::search:
        cmd::search(config, packages, verbose, force);
        break;
      case mode::remove:
        cmd::remove(config, packages, verbose, force);
        break;
      case mode::help:
        print_usage();
        break;
    }
  } else {
    print_usage();
  }
}

Config load_config(std::string fileName) {
  const auto data = toml::parse(fileName);
  Config config;
  config.repo_path = toml::find<std::string>(data, "repo_path");
  config.cache_path = toml::find<std::string>(data, "cache_path");
  return config;
}

void print_usage() {
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

}  // namespace owo
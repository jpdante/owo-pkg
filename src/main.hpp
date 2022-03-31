#pragma once

#include <clipp.h>

#include <filesystem>
#include <iostream>
#include <set>

#include "owopkg.hpp"

enum class Command { install, update, search, remove, help };

class Cli : public Logger {
 public:
  Cli(int argc, char* argv[]);
  ~Cli();

 private:
  std::filesystem::path configPath;
  std::filesystem::path repoPath;
  std::filesystem::path databasePath;
  std::filesystem::path cachePath;
  Command selectedCmd = Command::help;

 public:
  OwOPkg* client;
  std::set<std::string> packages;
  bool quiet = false;
  bool force = false;
  bool verbose = false;
  bool noRoot = false;

 private:
  bool ReadArguments(int argc, char* argv[]);
  void ProcessCommand();
  void EnsurePaths();
  void PrintUsage();

 public:
  void OnLog(LogType type, std::string message) override;
};
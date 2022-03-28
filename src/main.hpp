#pragma once

#include <clipp.h>

#include <filesystem>
#include <iostream>
#include <set>

#include "owopkg.hpp"
#include "shared.hpp"

enum class Command { install, update, search, remove, help };

class Cli {
 public:
  Cli(int argc, char* argv[]);
  ~Cli();

 private:
  std::filesystem::path configPath;
  std::filesystem::path databasePath;
  std::filesystem::path cachePath;

 public:
  OwOPkg* client;
  std::set<std::string> packages;
  bool quiet = false;
  bool force = false;
  bool verbose = false;
  bool noRoot = false;

 private:
  Command selectedCmd = Command::help;

 private:
  bool ReadArguments(int argc, char* argv[]);
  void ProcessCommand();
  void EnsurePaths();
  Config LoadConfig(std::filesystem::path fileName);
  void PrintUsage();
};
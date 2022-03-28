#pragma once

#include <string>
#include <filesystem>

struct Config {
 public:
  std::filesystem::path repositoryPath;
  std::filesystem::path cachePath;
  std::filesystem::path databasePath;

 public:
  Config();
  Config(std::filesystem::path repositoryPath, std::filesystem::path cachePath, std::filesystem::path databasePath);
};

class Shared {
 public:
  inline static Config config = Config();
};
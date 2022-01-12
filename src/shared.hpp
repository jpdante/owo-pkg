#pragma once

#include <string>

struct Config {
 public:
  std::string repositoryPath;
  std::string cachePath;

 public:
  Config();
  Config(std::string repositoryPath, std::string cachePath);
};

class Shared {
 public:
  inline static bool verbose = false;
  inline static bool force = false;
  inline static Config config = Config();
};
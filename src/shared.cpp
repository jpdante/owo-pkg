#include "shared.hpp"

Config::Config() {
  this->repositoryPath = "";
  this->cachePath = "";
}

Config::Config(std::filesystem::path repositoryPath, std::filesystem::path cachePath, std::filesystem::path databasePath) {
  this->repositoryPath = repositoryPath;
  this->cachePath = cachePath;
  this->databasePath = databasePath;
}
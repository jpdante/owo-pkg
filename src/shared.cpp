#include "shared.hpp"

Config::Config() {
  this->repositoryPath = "";
  this->cachePath = "";
}

Config::Config(std::string repositoryPath, std::string cachePath) {
  this->repositoryPath = repositoryPath;
  this->cachePath = cachePath;
}
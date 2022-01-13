#include "repository.hpp"

Repository::Repository(RepositoryConfig config, std::filesystem::path configPath) {
  this->enabled = config.enabled;
  this->name = config.name;
  this->url = config.url;
  this->supportsCompression = config.supportsCompression;
  this->configPath = configPath;
}

Repository::~Repository() {}
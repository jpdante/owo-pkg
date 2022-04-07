#include "repository-manager.hpp"

#include <iostream>
#include <toml.hpp>

namespace owo {

RepositoryManager::RepositoryManager(core::LoggerManager* loggerManager, std::filesystem::path repositoriesPath, std::filesystem::path cachePath) {
  this->loggerManager = loggerManager;
  this->logger = this->loggerManager->GetLogger();
  this->repositoriesPath = repositoriesPath;
  this->cachePath = cachePath;
}

RepositoryManager::~RepositoryManager() {
  for (Repository* repository : this->repositories) {
    delete repository;
  }
  this->repositories.clear();
  this->loggerManager->FreeLogger(this->logger);
}

void RepositoryManager::LoadRepositories() {
  this->repositories.clear();
  int count = 1;
  if (!std::filesystem::exists(this->repositoriesPath) || !std::filesystem::is_directory(this->repositoriesPath)) {
    if (!std::filesystem::create_directory(this->repositoriesPath)) {
      throw std::runtime_error("Failed to create directory " + this->repositoriesPath.generic_string());
    }
  }
  for (const auto& entry : std::filesystem::directory_iterator(this->repositoriesPath)) {
    if (entry.is_regular_file() || entry.is_symlink()) {
      try {
        const toml::value data = toml::parse(entry.path());
        if (!data.contains("name")) continue;
        if (!data.contains("url")) continue;

        bool enabled = toml::find_or<bool>(data, "enabled", true);
        std::string name = toml::find<std::string>(data, "name");
        std::string url = toml::find<std::string>(data, "url");
        bool supportsCompression = toml::find_or<bool>(data, "support_compression", false);

        if (name.empty()) throw std::runtime_error("Repository name at '" + entry.path().generic_string() + "' cannot be empty");
        if (url.empty()) throw std::runtime_error("Repository url at '" + entry.path().generic_string() + "' cannot be empty");

        logger->Info(std::to_string(count) + ":Found repository " + name);

        AddRepository(RepositoryConfig{enabled, name, url, supportsCompression});
      } catch (std::exception& ex) {
        logger->Error(std::to_string(count) + ":Exception: " + ex.what());
      }
      count++;
    }
  }
}

void RepositoryManager::AddRepository(RepositoryConfig config) {
  if (ContainsRepository(config.name)) {
    throw std::runtime_error("A repository with the name '" + config.name + "' already exists");
  }
  std::filesystem::path configPath = this->repositoriesPath / (config.name + ".toml");
  core::Logger* repoLogger = this->loggerManager->GetLogger();
  Repository* repository = new Repository(repoLogger, config, configPath, this->cachePath);
  repoLogger->prefix = std::to_string(this->repositories.size() + 1) + ":";
  this->repositories.push_back(repository);
}

Repository* RepositoryManager::GetRepository(std::string name) {
  for (Repository* repository : this->repositories) {
    if (repository->name == name) return repository;
  }
  return nullptr;
}

const std::list<Repository*>& RepositoryManager::GetRepositories() { return this->repositories; }

void RepositoryManager::RemoveRepository(Repository* repository) {
  this->repositories.remove(repository);
  delete repository;
  int count = 1;
  for (Repository* repo : this->repositories) {
    repo->logger->prefix = std::to_string(count) + ":";
    count++;
  }
}

bool RepositoryManager::ContainsRepository(Repository* repository) {
  for (Repository* repo : this->repositories) {
    if (repo == repository) return true;
  }
  return false;
}

bool RepositoryManager::ContainsRepository(std::string name) {
  for (Repository* repository : this->repositories) {
    if (repository->name == name) return true;
  }
  return false;
}

}  // namespace owo
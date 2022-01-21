#include "repository-manager.hpp"

#include <iostream>
#include <toml.hpp>

namespace owo {

RepositoryManager::RepositoryManager(std::filesystem::path repositoryPath, std::filesystem::path cachePath) {
  this->repositoryPath = repositoryPath;
  this->cachePath = repositoryPath;
  this->repositories.clear();
  LoadRepositories();
}

RepositoryManager::~RepositoryManager() {
  for (Repository* repository : this->repositories) {
    delete repository;
  }
  this->repositories.clear();
}

void RepositoryManager::LoadRepositories() {
  int count = 1;
  for (const auto& entry : std::filesystem::directory_iterator(this->repositoryPath)) {
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

        std::cout << count << ":Found repository " << name << std::endl;

        AddRepository(RepositoryConfig{enabled, name, url, supportsCompression});
      } catch (std::exception ex) {
        std::cout << count << ":Exception: " << ex.what() << std::endl;
      }
      count++;
    }
  }
}

void RepositoryManager::AddRepository(RepositoryConfig config) {
  if (ContainsRepository(config.name)) {
    throw std::runtime_error("A repository with the name '" + config.name + "' already exists");
  }
  std::filesystem::path configPath = this->repositoryPath / (config.name + ".toml");
  Repository* repository = new Repository(config, configPath);
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

}
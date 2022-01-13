#include "repository-manager.hpp"

RepositoryManager::RepositoryManager(std::filesystem::path repositoryPath, std::filesystem::path cachePath) {
  this->repositoryPath = repositoryPath;
  this->cachePath = repositoryPath;
  this->repositories.clear();
}

RepositoryManager::~RepositoryManager() {
  for (Repository* repository : this->repositories) {
    delete repository;
  }
  this->repositories.clear();
}

void RepositoryManager::AddRepository(RepositoryConfig config) {
  if (ContainsRepository(config.name)) {
    
  }
  std::filesystem::path configPath = this->repositoryPath / (config.name + ".toml");
  Repository* repository = new Repository(config, configPath);
  this->repositories.push_back(repository);
}

void RepositoryManager::UpdateRepositories() {
  for (Repository* repository : this->repositories) {
    UpdateRepository(repository);
  }
}

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
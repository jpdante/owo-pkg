#pragma once

#include <filesystem>
#include <list>

#include "repository.hpp"

class RepositoryManager {
 private:
  std::filesystem::path repositoryPath;
  std::filesystem::path cachePath;
  std::list<Repository*> repositories;

 public:
  RepositoryManager(std::filesystem::path repositoryPath, std::filesystem::path cachePath);
  ~RepositoryManager();

 public:
  void AddRepository(RepositoryConfig config);
  Repository* GetRepository(std::string name);
  std::list<Repository*>& GetRepositories(std::string name);
  void RemoveRepository(Repository* repository);
  bool ContainsRepository(Repository* repository);
  bool ContainsRepository(std::string name);
};
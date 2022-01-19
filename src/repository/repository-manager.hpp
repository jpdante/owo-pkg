#pragma once

#include <filesystem>
#include <list>

#include "repository.hpp"

namespace owo {

class RepositoryManager {
 private:
  std::filesystem::path repositoryPath;
  std::filesystem::path cachePath;
  std::list<Repository*> repositories;

 public:
  RepositoryManager(std::filesystem::path repositoryPath, std::filesystem::path cachePath);
  ~RepositoryManager();

 private:
  void LoadRepositories();

 public:
  void AddRepository(RepositoryConfig config);
  Repository* GetRepository(std::string name);
  const std::list<Repository*>& GetRepositories();
  void RemoveRepository(Repository* repository);
  bool ContainsRepository(Repository* repository);
  bool ContainsRepository(std::string name);
};

}
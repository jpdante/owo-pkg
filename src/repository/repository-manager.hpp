#pragma once

#include <filesystem>
#include <list>

#include "repository.hpp"

namespace owo {

class RepositoryManager {
 private:
  std::filesystem::path repositoriesPath;
  std::filesystem::path cachePath;
  std::list<Repository*> repositories;

 public:
  RepositoryManager(std::filesystem::path repositoriesPath, std::filesystem::path cachePath);
  ~RepositoryManager();

 public:
  void LoadRepositories();
  void AddRepository(RepositoryConfig config);
  Repository* GetRepository(std::string name);
  const std::list<Repository*>& GetRepositories();
  void RemoveRepository(Repository* repository);
  bool ContainsRepository(Repository* repository);
  bool ContainsRepository(std::string name);
};

}  // namespace owo
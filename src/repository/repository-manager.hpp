#pragma once

#include <filesystem>
#include <list>

#include "../core/logging.hpp"
#include "repository.hpp"

namespace owo {

class RepositoryManager {
 private:
  core::LoggerManager* loggerManager;
  core::Logger* logger;
  std::filesystem::path repositoriesPath;
  std::filesystem::path cachePath;
  std::list<Repository*> repositories;

 public:
  RepositoryManager(core::LoggerManager* loggerManager, std::filesystem::path repositoriesPath, std::filesystem::path cachePath);
  ~RepositoryManager();

 public:
  void FindRepositories();
  void AddRepository(RepositoryConfig config);
  Repository* GetRepository(std::string name);
  const std::list<Repository*>& GetRepositories();
  void RemoveRepository(Repository* repository);
  bool ContainsRepository(Repository* repository);
  bool ContainsRepository(std::string name);
};

}  // namespace owo
#pragma once

#include "repository.hpp"

class RepositoryManager {
 public:
  RepositoryManager();
  ~RepositoryManager();

 public:
  void AddRepository(RepositoryConfig config);
  void UpdateRepository(Repository repository);
  void UpdateRepositories();
  void RemoveRepository(Repository repository);
};
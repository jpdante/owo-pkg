#pragma once

#include <nlohmann/json.hpp>
#include <set>

#include "package.hpp"
#include "repo.hpp"

namespace cache {
class CachedRepository {
 public:
  CachedRepository();

 public:
  std::string name;
  std::string hash;
  std::set<Package> packages;
};

class CachedRepositories {
 public:
  CachedRepositories();

 private:
  std::set<CachedRepository*> cached_repositories;

 public:
  std::set<Package*> search(std::string name);
  void add_repository(CachedRepository* repo);
};

//CachedRepositories* load_cached_repositories(std::string path);

bool load_cached(std::string fileName, CachedRepository &cached);

bool update_cache(repo::RepositoryConfig* repositoryConfig);

}  // namespace cache
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
  std::string display_name;
  std::string url;
  std::string hash;
  std::string path;
  std::set<Package> packages;
};

class Cache {
 public:
  Cache();

 private:
  std::set<CachedRepository*> cached_repositories;

 public:
  std::set<Package*> search(std::string name);
  void add_repository(CachedRepository* repo);
};

Cache* load_cache(std::string path);

bool update_cache(CachedRepository* cachedRepository,
                  repo::Repository repository);

}  // namespace cache
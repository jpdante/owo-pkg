#include "cache.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>

namespace cache {

CachedRepository::CachedRepository() {}

Cache::Cache() {}

void Cache::add_repository(CachedRepository* repo) {
  this->cached_repositories.insert(repo);
}

std::set<Package*> Cache::search(std::string name) {
  std::set<Package*> packages;
  for (const auto& repo : this->cached_repositories) {
    for (auto package : repo->packages) {
      if (package.name.find(name) != std::string::npos) {
        packages.insert(&package);
        continue;
      }
      if (package.tags.find(name) != package.tags.end()) {
        packages.insert(&package);
        continue;
      }
    }
  }
  return packages;
}

Cache* load_cache(std::string path) {
  if (!std::filesystem::exists(path)) return nullptr;
  if (!std::filesystem::is_directory(path)) return nullptr;
  Cache* cache = new Cache();
  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    if (!entry.is_regular_file()) continue;
    std::filesystem::path entryPath = entry.path();
    if (entryPath.extension().string() != ".cr") continue;
    std::cout << "Found cached repo: " << entryPath.filename() << "\n";
    CachedRepository* repo = new CachedRepository();
    cache->add_repository(repo);
  }
  return cache;
}

bool update_cache(CachedRepository* cachedRepository,
                  repo::Repository repository) {
  std::fstream cacheFile;
  cacheFile.open(cachedRepository->path, std::ios::in | std::ios::out | std::ios::trunc);
  nlohmann::json cacheContent;
  cacheFile.close();
  return true;
}

}  // namespace cache
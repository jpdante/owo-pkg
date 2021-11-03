#include "cache.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace cache {

CachedRepository::CachedRepository() {}

CachedRepositories::CachedRepositories() {}

void CachedRepositories::add_repository(CachedRepository* repo) {
  this->cached_repositories.insert(repo);
}

std::set<Package*> CachedRepositories::search(std::string name) {
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

/*CachedRepositories* load_cache(std::string path) {
  if (!std::filesystem::exists(path)) return nullptr;
  if (!std::filesystem::is_directory(path)) return nullptr;
  CachedRepositories* cachedRepositories = new CachedRepositories();
  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    if (!entry.is_regular_file()) continue;
    std::filesystem::path entryPath = entry.path();
    if (entryPath.extension().string() != ".cr") continue;
    std::cout << "Found cached repo: " << entryPath.filename() << "\n";
    CachedRepository* repo = new CachedRepository();
    cachedRepositories->add_repository(repo);
  }
  return cachedRepositories;
}*/

bool load_cached(std::string fileName, CachedRepository& cached) {
  /*if (!std::filesystem::exists(fileName)) return false;
  if (!std::filesystem::is_regular_file(fileName)) return false;
  CachedRepository repository;
  std::fstream cacheFile;
  cacheFile.open(fileName, std::ios::in);
  nlohmann::json cacheContent;
  cacheFile >> cacheContent;
  cacheFile.close();
  if (!cacheContent["name"].is_string()) return false;
  if (!cacheContent["hash"].is_string()) return false;
  if (!cacheContent["packages"].is_array()) return false;
  repository.name = cacheContent["name"];
  repository.hash = cacheContent["hash"];
  for (auto pkg : cacheContent["packages"]) {
    Package package;
    package.name = pkg["name"];
    package.description = pkg["description"];
    package.latest_version = pkg["latest_version"];
    for (auto tag : pkg["tags"]) {
      package.tags.insert(tag.get<std::string>());
    }
    repository.packages.insert(package);
  }
  cached = repository;*/
  return true;
}

bool update_cache(CachedRepository* cachedRepository) {
  /*std::fstream cacheFile;
  cacheFile.open(cachedRepository->path, std::ios::in | std::ios::out |
  std::ios::trunc); nlohmann::json cacheContent; cacheFile.close();*/
  return true;
}

}  // namespace cache
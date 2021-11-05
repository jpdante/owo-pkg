#pragma once

#include <filesystem>
#include <iostream>
#include <nlohmann/json.hpp>
#include <set>
#include <vector>

#include "package.hpp"

namespace repo {

class RepositoryConfig {
 public:
  RepositoryConfig();

 public:
  int id;
  std::string name;
  std::string display_name;
  std::string url;
  std::string config_path;
  std::string config_fileName;
  bool support_compression;
};

class CachedRepository {
 public:
  CachedRepository(RepositoryConfig* config, nlohmann::json value);

 public:
  RepositoryConfig* config;
  std::set<Package> packages;
};

class CachedRepositories {
 public:
  CachedRepositories();

 private:
  std::set<CachedRepository*> cached_repositories;

 public:
  std::set<Package*> search(std::string value);
  void add_repository(CachedRepository* repo);
};

RepositoryConfig* read_repository_config(std::filesystem::path filePath);

std::vector<RepositoryConfig*> load_repositories_configs(
    std::filesystem::path dirPath);

bool load_repository(RepositoryConfig* repoConfig,
                     std::filesystem::path cachePath,
                     CachedRepository** cached);

bool check_update(RepositoryConfig* repository, std::filesystem::path cachePath,
                  bool verbose);

bool update_repository(RepositoryConfig* repository,
                       std::filesystem::path cache_path);

}  // namespace repo
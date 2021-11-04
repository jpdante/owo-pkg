#pragma once

#include <filesystem>
#include <iostream>
#include <set>
#include <vector>

#include "package.hpp"

namespace repo {

class RepositoryConfig {
 public:
  RepositoryConfig();

 public:
  std::string name;
  std::string display_name;
  std::string url;
  std::string config_path;
  std::string config_fileName;
  bool support_compression;
};

RepositoryConfig* read_repository(std::filesystem::path filePath);

std::vector<RepositoryConfig*> load_repositories(std::filesystem::path dirPath);

bool check_update(RepositoryConfig* repository, std::filesystem::path cachePath);

bool update_repository(RepositoryConfig* repository,
                       std::filesystem::path cache_path);

}  // namespace repo
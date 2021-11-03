#pragma once

#include <iostream>
#include <set>
#include <vector>

#include "package.hpp"

namespace repo {

class RepositoryConfig {
 public:
  RepositoryConfig(std::string name, std::string display_name, std::string url);

 public:
  std::string name;
  std::string display_name;
  std::string url;
  std::string path;
};

RepositoryConfig* read_repository(std::string file);

std::vector<RepositoryConfig*> load_repositories(std::string path);

bool check_update(RepositoryConfig* repository);

bool update_repository(RepositoryConfig* repository, std::string cache_path);

bool save_repository(RepositoryConfig* repository, std::string file);

}  // namespace repo
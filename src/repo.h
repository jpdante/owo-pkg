#pragma once

#include <iostream>
#include <set>

#include "package.h"

namespace repo {

class RepositoryConfig {
 public:
  RepositoryConfig(std::string name, std::string url);

 public:
  std::string name;
  std::string display_name;
  std::string url;
  std::string path;
};

class Repository {
 public:
  Repository();

 public:
  RepositoryConfig* repository_config;
  std::set<Package> packages;
};

RepositoryConfig* read_repository(std::string file);

bool save_repository(RepositoryConfig* repository, std::string file);

}  // namespace repo
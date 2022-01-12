#pragma once

#include <string>

struct RepositoryConfig {
  std::string name;
  std::string description;
  std::string url;
};

class Repository {
 public:
  std::string name;
  std::string description;
  std::string url;

 public:
  Repository(RepositoryConfig config);
  ~Repository();
};
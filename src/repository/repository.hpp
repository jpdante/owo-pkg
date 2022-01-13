#pragma once

#include <filesystem>
#include <string>

struct RepositoryConfig {
  bool enabled;
  std::string name;
  std::string url;
  bool supportsCompression;
};

class Repository {
 public:
  bool enabled;
  std::string name;
  std::string url;
  bool supportsCompression;
  std::filesystem::path configPath;

 public:
  Repository(RepositoryConfig config, std::filesystem::path configPath);
  ~Repository();
};
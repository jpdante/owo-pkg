#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>

#include "../core/http.hpp"
#include "../core/logging.hpp"

namespace owo {
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
  core::Logger* logger;

 private:
  bool loaded;
  std::filesystem::path cacheFilePath;
  std::unique_ptr<std::ifstream> packageStream;

 public:
  Repository(core::Logger* logger, RepositoryConfig config, std::filesystem::path configPath, std::filesystem::path cachePath);
  ~Repository();

 public:
  bool Load();
  void Unload();
  bool CheckUpdate();
  bool Update();
  bool ClearCache();
  std::list<std::string> SearchPackages(std::string packages);
  void LoadPackages();

 private:
  void Download(owo::core::HttpClient httpClient, bool useCompression);
};

}  // namespace owo
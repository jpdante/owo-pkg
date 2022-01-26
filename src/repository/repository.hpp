#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include "../core/http.hpp"

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

 private:
  bool loaded;
  std::filesystem::path cacheFilePath;
  std::ifstream* packageStream;

 public:
  Repository(RepositoryConfig config, std::filesystem::path configPath);
  ~Repository();

 public:
  bool LoadRepository();
  bool CheckUpdate(std::string logPrefix);
  bool UpdateRepository(std::string logPrefix);
  bool ClearCache();
  std::list<std::string> SearchPackages(std::string packages);

 private:
  void DownloadRepository(owo::core::HttpClient httpClient, bool useCompression);
};

}
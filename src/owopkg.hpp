#pragma once

#include <filesystem>

class OwOPkg {
 public:
  OwOPkg(std::filesystem::path repositoryPath, std::filesystem::path cachePath, std::filesystem::path databasePath);
  ~OwOPkg();

 public:
  void Init();
};
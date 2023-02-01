#pragma once

#include <filesystem>

#include "core/database.hpp"
#include "core/logging.hpp"
#include "repository/repository-manager.hpp"
#include "package/package-manager.hpp"
#include "package/package.hpp"

class OwOPkg {
 public:
  OwOPkg(std::filesystem::path repositoryPath, std::filesystem::path cachePath, std::filesystem::path databasePath);
  ~OwOPkg();

 private:
  std::filesystem::path repositoryPath;
  std::filesystem::path cachePath;
  std::filesystem::path databasePath;

  owo::core::LoggerManager* loggerManager;
  owo::core::Database* database;
  owo::core::Logger* logger;

  owo::RepositoryManager* repositoryManager;
  owo::PackageManager* packageManager;

 public:
  void Init();
  void RegisterAppender(owo::core::Appender* appender);
  void UnregisterAppender(owo::core::Appender* appender);

  // Repositories
  void LoadRepositories();
  void UpdateRepositories();
  void LoadPackages();
  owo::Package GetPackages();
};
#pragma once

#include <filesystem>

#include "core/database.hpp"
#include "core/logging.hpp"
#include "repository/repository-manager.hpp"

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
  owo::RepositoryManager* repositoryManager;
  owo::core::Logger* logger;

 public:
  void Init();
  void UpdateRepositories();
  void RegisterAppender(owo::core::Appender* appender);
  void UnregisterAppender(owo::core::Appender* appender);
};
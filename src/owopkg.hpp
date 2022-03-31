#pragma once

#include <filesystem>
#include <set>

#include "core/database.hpp"
#include "repository/repository-manager.hpp"

enum LogType { Verbose = 0, Info = 1, Error = 2, Fatal = 3 };

class Logger {
 public:
  virtual void OnLog(LogType type, std::string message) = 0;
};

class OwOPkg {
 public:
  OwOPkg(std::filesystem::path repositoryPath, std::filesystem::path cachePath, std::filesystem::path databasePath);
  ~OwOPkg();

 private:
  std::set<Logger*> loggers;
  std::filesystem::path repositoryPath;
  std::filesystem::path cachePath;
  std::filesystem::path databasePath;
  owo::core::Database* database;
  owo::RepositoryManager* repositoryManager;

 public:
  void Init();
  void RegisterLogger(Logger* logger);
  void UnregisterLogger(Logger* logger);
  void Log(LogType type, std::string message);
};
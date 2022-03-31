#include "owopkg.hpp"

OwOPkg::OwOPkg(std::filesystem::path repositoryPath, std::filesystem::path cachePath, std::filesystem::path databasePath) {
  this->repositoryPath = repositoryPath;
  this->cachePath = cachePath;
  this->databasePath = databasePath;
  this->database = new owo::core::Database(databasePath / "owo.db");
  this->repositoryManager = new owo::RepositoryManager(this->repositoryPath, this->cachePath);
}

OwOPkg::~OwOPkg() {
  if (this->repositoryManager) delete this->repositoryManager;
  if (this->database) delete this->database;
}

void OwOPkg::Init() {
  this->database->Init();
  this->repositoryManager->LoadRepositories();
}

void OwOPkg::RegisterLogger(Logger *logger) {
  if (loggers.find(logger) != loggers.end()) {
    throw new std::runtime_error("Logger already registered.");
  }
  loggers.insert(logger);
}

void OwOPkg::UnregisterLogger(Logger *logger) {
  if (loggers.find(logger) != loggers.end()) {
    loggers.erase(logger);
  }
}

void OwOPkg::Log(LogType type, std::string message) {
  for (Logger *logger : loggers) {
    try {
      logger->OnLog(type, message);
    } catch (std::exception) {
    }
  }
}
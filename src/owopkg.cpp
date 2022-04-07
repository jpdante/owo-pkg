#include "owopkg.hpp"

OwOPkg::OwOPkg(std::filesystem::path repositoryPath, std::filesystem::path cachePath, std::filesystem::path databasePath) {
  this->repositoryPath = repositoryPath;
  this->cachePath = cachePath;
  this->databasePath = databasePath;
  this->loggerManager = new owo::core::LoggerManager();
  this->logger = this->loggerManager->GetLogger();
  this->database = new owo::core::Database(databasePath / "owo.db");
  this->repositoryManager = new owo::RepositoryManager(this->loggerManager, this->repositoryPath, this->cachePath);
}

OwOPkg::~OwOPkg() {
  if (this->repositoryManager) delete this->repositoryManager;
  if (this->database) delete this->database;
  this->loggerManager->FreeLogger(logger);
  if (this->loggerManager) delete this->loggerManager;
}

void OwOPkg::Init() {
  this->database->Init();
  this->repositoryManager->LoadRepositories();
}

void OwOPkg::UpdateRepositories() {
  for (auto repository : this->repositoryManager->GetRepositories()) {
    try {
      repository->logger->Info("Checking " + repository->name + " for updates");
      if (repository->CheckUpdate()) {
        repository->UpdateRepository();
      }
    } catch (std::exception ex) {
      repository->logger->Error("Failed to update " + repository->name);
    }
  }
}

void OwOPkg::RegisterAppender(owo::core::Appender* appender) { this->loggerManager->RegisterAppender(appender); }

void OwOPkg::UnregisterAppender(owo::core::Appender* appender) { this->loggerManager->UnregisterAppender(appender); }
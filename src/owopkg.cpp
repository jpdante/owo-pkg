#include "owopkg.hpp"

OwOPkg::OwOPkg(std::filesystem::path repositoryPath, std::filesystem::path cachePath, std::filesystem::path databasePath) {
  this->repositoryPath = repositoryPath;
  this->cachePath = cachePath;
  this->databasePath = databasePath;
  this->logger = new owo::core::Logger();
  this->database = new owo::core::Database(databasePath / "owo.db");
  this->repositoryManager = new owo::RepositoryManager(this->logger, this->repositoryPath, this->cachePath);
}

OwOPkg::~OwOPkg() {
  if (this->repositoryManager) delete this->repositoryManager;
  if (this->database) delete this->database;
  if (this->logger) delete this->logger;
}

void OwOPkg::Init() {
  this->database->Init();
  this->repositoryManager->LoadRepositories();
}

void OwOPkg::UpdateRepositories() {
  int count = 1;
  for (auto repository : this->repositoryManager->GetRepositories()) {
    std::string prefix = std::to_string(count) + ":";
    try {
      this->logger->Info(prefix + "Checking " + repository->name + " for updates");
      if (repository->CheckUpdate(prefix)) {
        repository->UpdateRepository(prefix);
      }
    } catch (std::exception ex) {
      this->logger->Error(prefix + "Failed to update " + repository->name);
    }
    count++;
  }
}

void OwOPkg::RegisterAppender(owo::core::Appender* appender) { this->logger->RegisterAppender(appender); }

void OwOPkg::UnregisterAppender(owo::core::Appender* appender) { this->logger->UnregisterAppender(appender); }
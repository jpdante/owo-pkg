#include "logging.hpp"

namespace owo::core {

void LoggerManager::RegisterAppender(Appender *appender) {
  if (appenders.find(appender) != appenders.end()) {
    throw new std::runtime_error("Logger already registered.");
  }
  appenders.insert(appender);
}

void LoggerManager::UnregisterAppender(Appender *appender) {
  if (appenders.find(appender) != appenders.end()) {
    appenders.erase(appender);
  }
}

Logger *LoggerManager::GetLogger() {
  Logger *logger = new Logger(this);
  this->loggers.insert(logger);
  return logger;
}

void LoggerManager::FreeLogger(Logger *logger) {
  loggers.erase(logger);
  delete logger;
}

void LoggerManager::Log(LogType type, std::string message) {
  for (Appender *appender : appenders) {
    try {
      appender->OnLog(type, message);
    } catch (std::exception) {
    }
  }
}

Logger::Logger(LoggerManager *loggerManager) { this->loggerManager = loggerManager; }

void Logger::Log(LogType type, std::string message) { loggerManager->Log(type, prefix + message + suffix); }

void Logger::Free() { loggerManager->FreeLogger(this); }

}  // namespace owo::core
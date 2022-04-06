#include "logging.hpp"

namespace owo::core {

void Logger::RegisterAppender(Appender *appender) {
  if (appenders.find(appender) != appenders.end()) {
    throw new std::runtime_error("Logger already registered.");
  }
  appenders.insert(appender);
}

void Logger::UnregisterAppender(Appender *appender) {
  if (appenders.find(appender) != appenders.end()) {
    appenders.erase(appender);
  }
}

void Logger::Log(LogType type, std::string message) {
  for (Appender *appender : appenders) {
    try {
      appender->OnLog(type, message);
    } catch (std::exception) {
    }
  }
}

}
#pragma once

#include <set>
#include <stdexcept>
#include <string>

namespace owo::core {

enum LogType { Verbose = 0, Info = 1, Error = 2, Fatal = 3 };

class Appender {
 public:
  virtual void OnLog(LogType type, std::string message) = 0;
};

class LoggerManager;

class Logger {
 public:
  Logger(LoggerManager* loggerManager);

 private:
  LoggerManager* loggerManager;

 public:
  std::string prefix;
  std::string suffix;

 public:
  void Log(LogType type, std::string message);
  void Free();

  void Verbose(std::string message) { Log(LogType::Verbose, message); }
  void Info(std::string message) { Log(LogType::Info, message); }
  void Error(std::string message) { Log(LogType::Error, message); }
  void Fatal(std::string message) { Log(LogType::Fatal, message); }
};

class LoggerManager {
 private:
  std::set<Appender*> appenders;
  std::set<Logger*> loggers;

 public:
  void RegisterAppender(Appender* appender);
  void UnregisterAppender(Appender* appender);
  Logger* GetLogger();
  void FreeLogger(Logger* logger);
  void Log(LogType type, std::string message);
};

}  // namespace owo::core
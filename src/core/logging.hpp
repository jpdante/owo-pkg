#pragma once

#include <set>
#include <string>
#include <stdexcept>

namespace owo::core {

enum LogType { Verbose = 0, Info = 1, Error = 2, Fatal = 3 };

class Appender {
 public:
  virtual void OnLog(LogType type, std::string message) = 0;
};

class Logger {
 public:
  std::set<Appender*> appenders;

 public:
  void RegisterAppender(Appender* appender);
  void UnregisterAppender(Appender* appender);
  void Log(LogType type, std::string message);

  void Verbose(std::string message) { Log(LogType::Verbose, message); }
  void Info(std::string message) { Log(LogType::Info, message); }
  void Error(std::string message) { Log(LogType::Error, message); }
  void Fatal(std::string message) { Log(LogType::Fatal, message); }
};

}  // namespace owo::core
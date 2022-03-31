#pragma once

#include <sqlite3.h>

#include <filesystem>

namespace owo::core {

class Database {
 public:
  Database(std::filesystem::path dbPath);
  ~Database();

 private:
  std::filesystem::path dbPath;
  sqlite3 *sqlite3Db;

 public:
  void Init();
  void AddPackage();
  void UpdatePackage();
  void RemovePackage();
  bool CheckDatabase();
  void RepairDatabase();
};

}  // namespace owo::core
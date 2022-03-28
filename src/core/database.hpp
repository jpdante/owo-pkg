#pragma once

#include <filesystem>

namespace owo::core {

class Database {
 public:
  Database(std::filesystem::path dbPath);
  ~Database();

  public:
  void AddPackage();
  void UpdatePackage();
  void RemovePackage();
  bool CheckDatabase();
  void RepairDatabase();
};

}  // namespace owo::core
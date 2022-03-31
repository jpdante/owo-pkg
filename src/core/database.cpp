#include "database.hpp"

#include <iostream>
#include <sstream>

namespace owo::core {

Database::Database(std::filesystem::path dbPath) { this->dbPath = dbPath; }

Database::~Database() {
  if (sqlite3Db != nullptr) {
    sqlite3_close(sqlite3Db);
  }
}

void Database::Init() {
  int rc = sqlite3_open(dbPath.generic_string().c_str(), &sqlite3Db);
  if (rc) {
    std::string errorMsg = "Failed to open database: ";
    errorMsg.append(sqlite3_errmsg(sqlite3Db));
    errorMsg.append(".");
    throw std::runtime_error(errorMsg);
  }
  char const* sql = "CREATE TABLE IF NOT EXISTS package (id TEXT, version TEXT, branch TEXT);";
  char* zErrMsg = 0;
  rc = sqlite3_exec(sqlite3Db, sql, 0, 0, &zErrMsg);
  if (rc != SQLITE_OK) {
    std::string errorMsg = "Failed to create 'package' table: ";
    errorMsg.append(zErrMsg);
    errorMsg.append(".");
    sqlite3_free(zErrMsg);
    throw std::runtime_error(errorMsg);
  }
}

void Database::AddPackage() {}

void Database::UpdatePackage() {}

void Database::RemovePackage() {}

bool Database::CheckDatabase() {
  return true;
}

void Database::RepairDatabase() {}

}  // namespace owo::core
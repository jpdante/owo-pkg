#include "database.hpp"

#include <sqlite3.h>

#include <iostream>
#include <sstream>

namespace owo::core {

Database::Database(std::filesystem::path dbPath) {
  std::cout << dbPath << std::endl;
  sqlite3 *db;
  sqlite3_open((dbPath / "owo.db").generic_string().c_str(), &db);
  sqlite3_close(db);
}
Database::~Database() {}

}  // namespace owo::core
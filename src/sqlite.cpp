#include "sqlite.h"

#include <functional>
#include <iostream>
#include <mutex>
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <vector>

std::vector<DatabaseCallback> Sqlite::sqlCallbacks_{};

bool Sqlite::execute_sql(const std::string &sql, DatabaseCallback callback) {
  static std::mutex databaseLock{};
  std::lock_guard<std::mutex> lock(databaseLock);
  char *zErrMsg{nullptr};
  sqlCallbacks_.emplace_back(callback);

  int rc = sqlite3_exec(db, sql.c_str(), Sqlite::sqlCallback,
                        reinterpret_cast<void *>(sqlCallbacks_.size() - 1),
                        &zErrMsg);
  if (rc != SQLITE_OK) {
    std::cerr << "Can't execute command on database " << databaseName_
              << ", error: " << zErrMsg;
    sqlite3_free(zErrMsg);
    return false;
  }
  return true;
}

bool Sqlite::open(const std::string name) {
  char *zErrMsg = 0;
  int rc;

  databaseName_ = name;
  rc = sqlite3_open(name.c_str(), &db);

  if (rc) {
    std::cerr << "Can't open database with name" << name << ": " << zErrMsg;
    return false;
  }
  return true;
}

bool Sqlite::init(const std::string name) {
  const std::string sql = R"(
CREATE TABLE IF NOT EXISTS devicelog (
 id INTEGER PRIMARY KEY AUTOINCREMENT,
 timestamp  DATETIME default current_timestamp,
 device TEXT NOT NULL,
 deviceName TEXT NOT NULL
      );
      )";
  return execute_sql(sql);
}

bool Sqlite::close() {
  sqlite3_close(db);
  return true;
}

bool Sqlite::write(const DeviceEntry entry) {
  std::stringstream sql;
  sql << " INSERT INTO devicelog (device, deviceName)"
      << "VALUES ('" << entry.first << "', '" << entry.second << "')"
      << ";";
  std::string sqlstr = sql.str();
  return execute_sql(sqlstr);
}
bool Sqlite::insert(const std::vector<std::string> data) {
  if (data.size() % 2 != 0)
    return false;

  for (auto entry = data.begin(); entry != data.end(); entry += 2) {
    if (!write(std::make_pair(*entry, *std::next(entry))))
      return false;
  }

  return true;
}

bool Sqlite::select(const std::string sql, DatabaseCallback callback) {
  return execute_sql(sql, callback);
}

bool Sqlite::executeSql(const std::string &string) {
  return execute_sql(string);
}

int Sqlite::sqlCallback(void *data, int argc, char **argv, char **azColName) {
  size_t callbackNr = reinterpret_cast<size_t>(data);
  std::vector<DatabaseEntry> values;

  for (int i{0}; i < argc; i++) {
    std::string columnName = azColName[i];
    std::string value = argv[i] ? argv[i] : "NULL";
    values.push_back(std::make_pair(columnName, value));
  }
  auto callback = sqlCallbacks_.at(callbackNr);
  if (callback) {
    callback(values);
  };
  sqlCallbacks_.erase(sqlCallbacks_.begin() + callbackNr);
  return 0;
}

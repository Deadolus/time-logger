#pragma once

#include <string>
#include <vector>
#include <functional>
#include <sqlite3.h>

typedef std::pair<std::string, std::string> DatabaseEntry;
typedef std::function<void(std::vector<DatabaseEntry>&)> DatabaseCallback;

class Sqlite {
  public:
    bool open(const std::string name="database.db");
    bool init(const std::string name="database.db");
    bool close();
    bool insert(const std::vector<std::string> data);
    bool executeSql(const std::string& string);
    bool select(const std::string sql, DatabaseCallback callback);
  private:
      static int sqlCallback(void *data, int argc, char **argv, char **azColName);
    bool execute_sql(const std::string& sql, DatabaseCallback callback = {});
    sqlite3 *db;
    std::string databaseName_;
    static std::vector<DatabaseCallback> sqlCallbacks_;

    };

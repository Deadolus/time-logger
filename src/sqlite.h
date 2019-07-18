#pragma once

#include <string>
#include <vector>
#include <functional>
#include <sqlite3.h>

typedef std::pair<std::string, std::string> DatabaseEntry;
typedef std::function<void(std::vector<DatabaseEntry>&)> DatabaseCallback;

class Sqlite {
  public:
    bool open(std::string name="database.db");
    bool init(std::string name="database.db");
    bool close();
    bool insert(std::vector<std::string> data);
    bool executeSql(std::string& string);
    bool select(std::string sql, DatabaseCallback callback);
  private:
      static int sqlCallback(void *data, int argc, char **argv, char **azColName);
    bool execute_sql(std::string& sql, DatabaseCallback& callback);
    sqlite3 *db;
    static std::vector<DatabaseCallback> sqlCallbacks_;

    };

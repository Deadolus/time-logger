#pragma once

#include <string>
#include <vector>
#include <sqlite3.h>

class Sqlite {
  public:
    bool open(std::string name="database.db");
    bool init(std::string name="database.db");
    bool close();
    bool insert(std::vector<std::string> data);
    bool executeSql(std::string& string);
    bool select(std::string sql, sqlite3_callback callback=sqlCallback);
  private:
      static int sqlCallback(void *data, int argc, char **argv, char **azColName);
    bool execute_sql(std::string& sql, sqlite3_callback callback=nullptr, void* data=nullptr);
      sqlite3 *db;

    };

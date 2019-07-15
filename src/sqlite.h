#pragma once

#include <string>
#include <vector>
#include <sqlite3.h>

//static int sqlCallback(void *data, int argc, char **argv, char **azColName);
class Sqlite {
  public:
    bool open(std::string name="database.db");
    bool init(std::string name="database.db");
    bool close();
    bool insert(std::vector<std::string> data);
    bool executeSql(std::string& string);
    bool select(std::string sql);
    //friend int sqlCallback(void *data, int argc, char **argv, char **azColName){
  private:
    bool execute_sql(std::string& sql, sqlite3_callback callback=nullptr, void* data=nullptr);
      void gatherData(std::vector<std::string> data);
      sqlite3 *db;

    };

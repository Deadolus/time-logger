#include "sqlite.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <sqlite3.h>

namespace {
  static int sqlCallback(void *data, int argc, char **argv, char **azColName){
    Sqlite* instance = static_cast<Sqlite*>(data);
    //fprintf(stderr, "%s: ", (const char*)data);
    std::vector<std::string> values;

    for(int i{0}; i<argc; i++){
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      values.push_back(argv[i] ? argv[i] : "NULL");
    }
    //instance->gatherData(values);

    return 0;
  }

}

bool Sqlite::execute_sql(std::string& sql, sqlite3_callback callback, void* data) {
  char* zErrMsg{nullptr};
  int rc = sqlite3_exec(db,sql.c_str(),callback, data, &zErrMsg);
  if( rc != SQLITE_OK ){
    std::cerr << "Can't execute command, error: " << zErrMsg;
    sqlite3_free(zErrMsg);
    return false;
  }
  return true;
}

bool Sqlite::open(std::string name) {
  char *zErrMsg = 0;
  int rc;

  rc = sqlite3_open(name.c_str(), &db);

  if( rc ) {
    std::cerr << "Can't open database: " << zErrMsg;
    return false;
  }
  return true;
}

bool Sqlite::init(std::string name) {
  std::string sql = R"(
CREATE TABLE IF NOT EXISTS devicelog (
 id INTEGER PRIMARY KEY AUTOINCREMENT,
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

bool Sqlite::insert(std::vector<std::string> data) {
  std::stringstream sql;
  sql <<  " INSERT INTO devicelog (device, deviceName)"
    << "VALUES ('" << data[0] <<"', '"<< data[1] <<"')"
    << ";";
  std::string  sqlstr = sql.str();
  return execute_sql(sqlstr);
}

bool Sqlite::select(std::string /*sql*/) {
  std::string sql = R"(
      SELECT * from devicelog
      )";
  return execute_sql(sql, sqlCallback);
}

bool Sqlite::executeSql(std::string& string) {
  return execute_sql(string);
}

void Sqlite::gatherData(std::vector<std::string> data) {

}

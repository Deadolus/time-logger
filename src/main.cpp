#include "sqlite.h"
int main(void)
{
  Sqlite sqlite;
  sqlite.open();
  sqlite.close();
  return 0;
}

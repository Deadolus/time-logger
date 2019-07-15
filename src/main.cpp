#include "sqlite.h"
#include "bluetooth.h"
int main(void)
{
  Sqlite sqlite;
  sqlite.open();
  sqlite.close();
  Bluetooth bluetooth;
  bluetooth.scan();
  return 0;
}

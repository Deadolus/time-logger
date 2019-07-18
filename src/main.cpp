#include "sqlite.h"
#include "bluetooth.h"
#include "ping.h"

#include <iostream>

int main(void)
{
  Sqlite sqlite;
  sqlite.open();
  sqlite.init();
  Bluetooth bluetooth;
  Pinger pinger;
  auto devices = bluetooth.scan();
  for(auto& device : devices) {

    std::cout << device.first << "," << device.second << std::endl;
    sqlite.insert({device.first, device.second});
  }
  devices = pinger.scan();
  for(auto& device : devices) {

    std::cout << device.first << "," << device.second << std::endl;
    sqlite.insert({device.first, device.second});
  }

  sqlite.close();
  return 0;
}

#include "sqlite.h"
#include "bluetoothScanner.h"
#include "pingScanner.h"

#include <iostream>
#include <thread>

int main(void)
{
  Sqlite sqlite;
  sqlite.open();
  sqlite.init();
  BluetoothScanner bluetooth;
  PingScanner pinger;

  auto scanService = [](Scanner& scanner, Writer& writer){
  auto devices = scanner.scan();
  for(auto& device : devices) {
    std::cout << device.first << "," << device.second << std::endl;
    writer.write(device);
  }
  };

  std::thread bluetoothThread (scanService, std::ref(bluetooth), std::ref(sqlite));
  std::thread pingThread (scanService, std::ref(pinger), std::ref(sqlite));
  bluetoothThread.join();
  pingThread.join();

  sqlite.close();
  return 0;
}

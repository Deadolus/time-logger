#pragma once

#include "scanner.h"

class BluetoothScanner : public Scanner {
public:
  DeviceList scan(void) override;
};

#pragma once

#include "scanner.h"

class Bluetooth : public Scanner {
  public:
    DeviceList scan(void) override;
};

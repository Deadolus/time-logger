#pragma once

#include "scanner.h"

class PingScanner : public Scanner {
  public:
    DeviceList scan(void) override;
};

#pragma once

#include "scanner.h"

class Pinger : public Scanner {
  public:
    DeviceList scan(void) override;
};

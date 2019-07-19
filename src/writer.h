#pragma once

#include <string>

typedef std::pair<std::string, std::string> DeviceEntry;

class Writer {
  public:
    virtual bool write(const DeviceEntry entry) = 0;
    };

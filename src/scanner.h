
#pragma once

#include <vector>
#include <string>

typedef std::vector<std::pair<std::string, std::string>> DeviceList;
class Scanner {
  public:
    virtual DeviceList scan(void) = 0;
};

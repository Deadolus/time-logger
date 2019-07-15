#pragma once

#include <vector>
#include <string>
class Bluetooth {
  public:
    std::vector<std::pair<std::string, std::string>> scan(void);
};

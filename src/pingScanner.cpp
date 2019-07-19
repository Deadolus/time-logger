#include "pingScanner.h"
#include "fmt/format.h"
#include "pstream.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace {
const std::string ipRange = "192.168.1.1/24";
const std::string command = "nmap -v -sn " + ipRange +
                            " --open -oG - | grep Host | awk '{ print $2,$3 }'";
} // end of anonymous namespace

DeviceList PingScanner::scan(void) {
  DeviceList devices;
  auto cleanUpName = [](std::string &name) {
    name.erase(std::remove(name.begin(), name.end(), '('), name.end());
    name.erase(std::remove(name.begin(), name.end(), ')'), name.end());
  };
  redi::ipstream in(command);
  std::vector<std::string> output;
  std::string line;
  while (in >> line) {
    output.push_back(line);
  }
  for (auto device = output.begin(); device != output.end(); device += 2) {
    std::string ip = *device;
    std::string name = *std::next(device);
    cleanUpName(name);
    devices.push_back(
        std::make_pair<std::string, std::string>(ip.c_str(), name.c_str()));
  }
  return devices;
}

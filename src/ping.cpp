#include "ping.h"
#include "fmt/format.h"
#include "pstream.h"

#include <iostream>
#include <vector>
#include <algorithm>

namespace {
const std::string command = "nmap -v -sn 192.168.1.1/24 --open -oG - | grep Host | awk '{ print $2,$3 }'";
}

DeviceList Pinger::scan(void) {
  DeviceList devices;
  auto cleanUpName = [](std::string& name){
      name.erase (std::remove(name.begin(), name.end(), '('), name.end());
      name.erase (std::remove(name.begin(), name.end(), ')'), name.end());
  };
  redi::ipstream in(command);
  std::vector<std::string> output;
    std::string line;
  while(in >> line) {
    output.push_back(line);
  }
    for(auto device = output.begin(); device != output.end(); device+=2) {
      std::string ip = *device;
      std::string name = *std::next(device);
      cleanUpName(name);
      devices.push_back(std::make_pair<std::string, std::string>(ip.c_str(), name.c_str()));
    }
  return devices;
}

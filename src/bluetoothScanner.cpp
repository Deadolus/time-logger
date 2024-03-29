#include "bluetoothScanner.h"

#include <array>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>

std::vector<std::pair<std::string, std::string>> BluetoothScanner::scan(void) {
  constexpr int max_rsp = 255;
  constexpr int len = 8;
  constexpr int flags = IREQ_CACHE_FLUSH;
  unsigned int num_rsp{};
  int dev_id{};
  int sock{};
  std::array<inquiry_info, max_rsp> ii2{};
  inquiry_info *ii = ii2.data(); // ugly
  std::vector<std::pair<std::string, std::string>> devices{};

  dev_id = hci_get_route(nullptr);
  sock = hci_open_dev(dev_id);
  if (dev_id < 0 || sock < 0) {
    perror("opening socket");
    return devices;
  }

  num_rsp = hci_inquiry(dev_id, len, max_rsp, nullptr, &ii, flags);
  if (num_rsp < 0)
    perror("hci_inquiry");

  for (unsigned int i{0}; i < num_rsp; i++) {
    std::array<char, 19> addr{};
    std::array<char, max_rsp> name{};
    ba2str(&(ii + i)->bdaddr, addr.data());
    if (hci_read_remote_name(sock, &(ii + i)->bdaddr, sizeof(name), name.data(),
                             0) < 0)
      strncpy(name.data(), "[unknown]", name.size());
    devices.push_back(
        std::make_pair<std::string, std::string>(addr.data(), name.data()));
  }

  close(sock);
  return devices;
}

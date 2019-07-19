#include "bluetoothScanner.h"
#include "gtest/gtest.h"

#include <string>

class BluetoothScannerTest : public ::testing::Test {
protected:
  BluetoothScanner scanner{};
};

TEST(BluetoothScannerSimpleTest, can_execute_scan) {
  BluetoothScanner scanner{};
  EXPECT_GE(scanner.scan().size(), 0ul);
}

#include "gtest/gtest.h"
#include "bluetoothScanner.h"

#include <string>

class BluetoothTest : public ::testing::Test
{
    protected:
      BluetoothScanner scanner{};
};

TEST(BluetoothSimpleTest, can_execute_scan)
{
  BluetoothScanner scanner{};
  EXPECT_GE(scanner.scan().size(), 0);
}


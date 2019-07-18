#include "gtest/gtest.h"
#include "bluetooth.h"

#include <string>

class BluetoothTest : public ::testing::Test
{
    protected:
      Bluetooth scanner{};
};

TEST(BluetoothSimpleTest, can_execute_scan)
{
  Bluetooth scanner{};
  EXPECT_GE(scanner.scan().size(), 0);
}


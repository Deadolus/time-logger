#include "gtest/gtest.h"
#include "bluetooth.h"

#include <string>

class PingerTest : public ::testing::Test
{
    protected:
      Bluetooth scanner{};
};

TEST(SimpleBluetoothTest, can_execute_scan)
{
  Bluetooth scanner{};
  EXPECT_GE(scanner.scan().size(), 0);
}


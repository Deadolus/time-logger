#include "gtest/gtest.h"
#include "ping.h"

#include <string>

class PingerTest : public ::testing::Test
{
    protected:
      Pinger pinger{};
};

TEST(SimplePingerTest, can_execute_scan)
{
  Pinger scanner{};
  EXPECT_GE(scanner.scan().size(), 0);
}


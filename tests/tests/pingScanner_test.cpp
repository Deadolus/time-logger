#include "gtest/gtest.h"
#include "pingScanner.h"

#include <string>

class PingerTest : public ::testing::Test
{
    protected:
      PingScanner scanner{};
};

TEST(SimplePingerTest, can_execute_scan)
{
  PingScanner scanner{};
  EXPECT_GE(scanner.scan().size(), 0);
}


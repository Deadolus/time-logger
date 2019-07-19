#include "gtest/gtest.h"
#include "pingScanner.h"

#include <string>

class PingScannerTest : public ::testing::Test
{
    protected:
      PingScanner scanner{};
};

TEST(PingScannerSimpleTest, can_execute_scan)
{
  PingScanner scanner{};
  EXPECT_GE(scanner.scan().size(), 0);
}


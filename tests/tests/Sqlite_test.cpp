#include "gtest/gtest.h"
#include "sqlite.h"

#include <string>


class SqliteTest : public ::testing::Test
{
    protected:
      Sqlite sqlite{};
      void SetUp() override {
        EXPECT_TRUE(sqlite.open("testdatabase.db"));
      }

      void TearDown()  override {
        std::string sql = "DROP TABLE devicelog;";
        EXPECT_TRUE(sqlite.executeSql(sql));
        EXPECT_TRUE(sqlite.close());
      }
};

TEST(SimpleSqliteTest, can_open_and_close_database)
{
  Sqlite sqlite{};
  EXPECT_TRUE(sqlite.open("testdatabase.db"));
  EXPECT_TRUE(sqlite.close());
}

TEST_F(SqliteTest, can_init_database)
{
    EXPECT_TRUE(sqlite.init());
}

TEST_F(SqliteTest, can_insert_values)
{
  std::vector<std::string> value{"00x00", "device"};
    EXPECT_TRUE(sqlite.init());
    EXPECT_TRUE(sqlite.insert(value));
}

TEST_F(SqliteTest, count_is_correct_after_insert)
{
  std::vector<std::string> value{"00x00", "device"};
    EXPECT_TRUE(sqlite.init());
    EXPECT_TRUE(sqlite.insert(value));
    EXPECT_TRUE(sqlite.select(value[0]));
}





#include "gtest/gtest.h"
#include "sqlite.h"

#include <string>
#include <cstdio>

namespace {
  class UniqueDatabase {
    public:
      UniqueDatabase() {
        name_ = std::tmpnam(nullptr) +std::string(".db");
        std::cout << "My new database name: " << name_ << std::endl;
      }
      ~UniqueDatabase() {
        std::remove(name_.c_str());
      }
      const std::string getName() { return name_;}
    private:
      std::string name_;
  };
} // end anonymous namespace

class SqliteTest : public ::testing::Test
{
  protected:
    Sqlite sqlite{};
    void SetUp() override {
      EXPECT_TRUE(sqlite.open(database.getName()));
    }

    void TearDown()  override {
      std::string sql = "DROP TABLE devicelog;";
      EXPECT_TRUE(sqlite.executeSql(sql));
      EXPECT_TRUE(sqlite.close());
    }
  private:
    UniqueDatabase database;
};

TEST(SqliteSimpleTest, can_open_and_close_database)
{
  Sqlite sqlite{};
  UniqueDatabase database;
  EXPECT_TRUE(sqlite.open((database.getName())));
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
  std::string sql = "SELECT * FROM devicelog;";
  DatabaseCallback cb = [](std::vector<DatabaseEntry>& entries){
    EXPECT_EQ(entries.size(), 4);
  };
  EXPECT_TRUE(sqlite.init());
  EXPECT_TRUE(sqlite.insert(value));
  EXPECT_TRUE(sqlite.select(sql, cb));
}

TEST_F(SqliteTest, entry_is_correct_after_insert)
{
  std::vector<std::string> value{"00x00", "device"};
  std::string sql = "SELECT * FROM devicelog;";
  DatabaseCallback cb = [](std::vector<DatabaseEntry>& entries){
    //for(auto& entry : entries) { std::cout << entry.first << "/"<<entry.second << std::endl; }
    EXPECT_EQ(entries[0].second, "1");
    //entries[1] is datetime and thus variable
    EXPECT_EQ(entries[2].second, "00x00");
    EXPECT_EQ(entries[3].second, "device");
  };
  sqlite.init();
  sqlite.insert(value);
  sqlite.select(sql, cb);
}




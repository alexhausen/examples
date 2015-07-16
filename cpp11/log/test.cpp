#include <gtest/gtest.h>
#include "log.h"

namespace log {

TEST(LogLevel, level_values) {
  EXPECT_EQ(0, static_cast<int>(level::error));
  EXPECT_EQ(1, static_cast<int>(level::warning));
  EXPECT_TRUE(level::error < level::warning);
  EXPECT_TRUE(level::warning < level::info);
  EXPECT_TRUE(level::info < level::debug);
}

TEST(LogLevel, level_names) {
  EXPECT_EQ("E", to_string(level::error));
  EXPECT_EQ("W", to_string(level::warning));
  EXPECT_EQ("I", to_string(level::info));
  EXPECT_EQ("D", to_string(level::debug));
  EXPECT_EQ("D", to_string(static_cast<level>(-1)));
  EXPECT_EQ("D", to_string(static_cast<level>(10)));
}

class LogTest : public ::testing::Test {
 protected:
  LogTest() { }
  virtual ~LogTest() { }
  virtual void SetUp() {
    reset();
  }
  virtual void TearDown() {
  }
};

TEST_F(LogTest, reset) {
  EXPECT_NO_THROW(reset());
  EXPECT_TRUE(ls().empty());
  EXPECT_TRUE(enabled());
  //?others?
}

TEST_F(LogTest, add_category) {
  add("cat1");
  std::map<std::string, bool> l = ls();
  EXPECT_EQ(1u, l.size());
  EXPECT_NO_THROW( EXPECT_FALSE(l.at("cat1")) );
}

TEST_F(LogTest, unblock_category) {
  add("cat1");
  unblock("cat1");
  EXPECT_EQ(1u, ls().size());
  EXPECT_NO_THROW( EXPECT_FALSE(blocked("cat1")) );
}

TEST_F(LogTest, block_category) {
  add("cat1");
  unblock("cat1");
  block("cat1");
  EXPECT_EQ(1u, ls().size());
  EXPECT_NO_THROW( EXPECT_TRUE(blocked("cat1")) );
}

TEST_F(LogTest, unblock_star) {
  add("cat1");
  add("cat2");
  EXPECT_EQ(2u, ls().size());  
  unblock("*");
  EXPECT_NO_THROW( EXPECT_FALSE(blocked("cat1")) );
  EXPECT_NO_THROW( EXPECT_FALSE(blocked("cat2")) );
}

TEST_F(LogTest, block_star) {
  add("cat1");
  add("cat2");
  EXPECT_EQ(2u, ls().size());
  EXPECT_NO_THROW( EXPECT_TRUE(blocked("cat1")) );
  EXPECT_NO_THROW( EXPECT_TRUE(blocked("cat2")) );
  unblock("*");
  EXPECT_NO_THROW( EXPECT_FALSE(blocked("cat1")) );
  EXPECT_NO_THROW( EXPECT_FALSE(blocked("cat2")) );
  block("*");
  EXPECT_EQ(2u, ls().size());  
  EXPECT_NO_THROW( EXPECT_TRUE(blocked("cat1")) );
  EXPECT_NO_THROW( EXPECT_TRUE(blocked("cat2")) );
}

TEST_F(LogTest, stream) {
  FAIL();
}

TEST_F(LogTest, output_to_disabled_category) {
  FAIL();  
}

TEST_F(LogTest, output_to_disabled_level) {
  FAIL();  
}


}


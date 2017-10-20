#include "parser.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <cstring>
#include "callback.h"

using ::testing::_;

MATCHER_P2(ByteBufferMatcher, buffer, length, "") {
  return std::equal(arg, arg + length, buffer);
}

class mock_callback : public callback {
 public:
  virtual ~mock_callback() {}
  MOCK_CONST_METHOD2(fn, void(const uint8_t*, size_t));
};

TEST(parser, OnePacket) {
  mock_callback mcb;
  parser p1{mcb};
  uint8_t data[32];
  std::memset(data, 0xFF, 32);

  uint8_t expected[32];
  std::memset(expected, 0xFF, 32);

  EXPECT_CALL(mcb, fn(ByteBufferMatcher(expected, 32), 32)).Times(1);

  p1.parse(data, 32);

  ASSERT_EQ(0, p1.temp_buffer_size_);
}

TEST(parser, TwoPackets) {
  mock_callback mcb;
  parser p1{mcb};

  uint8_t data[32];
  std::memset(data, 0xFF, 32);

  uint8_t expected[32];
  std::memset(expected, 0xFF, 32);

  EXPECT_CALL(mcb, fn(ByteBufferMatcher(expected, 32), 32)).Times(2);

  p1.parse(data, 32);
  p1.parse(data, 32);

  ASSERT_EQ(0, p1.temp_buffer_size_);
}

TEST(parser, HalfPacket) {
  mock_callback mcb;
  parser p1{mcb};

  uint8_t data[16];
  std::memset(data, 0xFF, 16);

  p1.parse(data, 16);

  ASSERT_EQ(16, p1.temp_buffer_size_);
}

TEST(parser, TwoHalfPackets) {
  mock_callback mcb;
  parser p1{mcb};

  uint8_t data[16];
  std::memset(data, 0xFF, 16);

  uint8_t expected[32];
  std::memset(expected, 0xFF, 32);

  EXPECT_CALL(mcb, fn(ByteBufferMatcher(expected, 32), 32)).Times(1);

  p1.parse(data, 16);
  p1.parse(data, 16);

  ASSERT_EQ(0, p1.temp_buffer_size_);
}

TEST(parser, ThreeHalfPackets) {
  mock_callback mcb;
  parser p1{mcb};

  uint8_t data[16];
  std::memset(data, 0xFF, 16);

  uint8_t expected[32];
  std::memset(expected, 0xFF, 32);

  EXPECT_CALL(mcb, fn(ByteBufferMatcher(expected, 32), 32)).Times(1);

  p1.parse(data, 16);
  p1.parse(data, 16);
  p1.parse(data, 16);

  ASSERT_EQ(16, p1.temp_buffer_size_);
}

TEST(parser, OneHalfPacketPlusOneFullPacket) {
  mock_callback mcb;
  parser p1{mcb};

  uint8_t data1[16];
  std::memset(data1, 0xFF, 16);

  uint8_t data2[32];
  std::memset(data2, 0xFF, 32);

  uint8_t expected[32];
  std::memset(expected, 0xFF, 32);

  EXPECT_CALL(mcb, fn(ByteBufferMatcher(expected, 32), 32)).Times(1);

  p1.parse(data1, 16);
  p1.parse(data2, 32);

  ASSERT_EQ(16, p1.temp_buffer_size_);
}

// 1 packet of n-1 bytes, 1 packet of n bytes => 1 calls to fn(), n-1 temp_size
TEST(parser, 31_plus_32) {
  mock_callback mcb;
  parser p1{mcb};

  uint8_t data1[31];
  std::memset(data1, 0xFF, 31);

  uint8_t data2[32];
  std::memset(data2, 0xFF, 32);
  
  uint8_t expected[32];
  std::memset(expected, 0xFF, 32);

  EXPECT_CALL(mcb, fn(ByteBufferMatcher(expected, 32), 32)).Times(1);
  
  p1.parse(data1, 31);
  p1.parse(data2, 32);

  ASSERT_EQ(31, p1.temp_buffer_size_);
}

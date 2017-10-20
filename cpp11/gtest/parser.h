#pragma once

#include <cstdint>
#include <cstdlib>

#include "gtest/gtest_prod.h"

class callback;

#define PACKET_SIZE 32

class parser {
 public:
  parser(const callback& cb);
  void parse(const uint8_t* p, size_t n);

 private:
  const callback& cb_;
  size_t temp_buffer_size_;
  uint8_t temp_buffer_[2 * PACKET_SIZE];

  FRIEND_TEST(parser, OnePacket);
  FRIEND_TEST(parser, TwoPackets);
  FRIEND_TEST(parser, HalfPacket);
  FRIEND_TEST(parser, TwoHalfPackets);
  FRIEND_TEST(parser, ThreeHalfPackets);
  FRIEND_TEST(parser, OneHalfPacketPlusOneFullPacket);
  FRIEND_TEST(parser, 31_plus_32);
};

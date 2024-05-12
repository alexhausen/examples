#include <cassert>
#include <cstring>
#include <iostream>

#include "callback.h"
#include "parser.h"

parser::parser(const callback& cb) : cb_{cb}, temp_buffer_size_{0} {
  std::memset(temp_buffer_, 0, 2 * PACKET_SIZE);
}

void parser::parse(const uint8_t* ptr, size_t n) {
  assert(ptr);
  assert(0 < n && n <= PACKET_SIZE);

  memcpy(&temp_buffer_[temp_buffer_size_], ptr, n);
  temp_buffer_size_ += n;
  ptr = temp_buffer_;

  if (temp_buffer_size_ >= PACKET_SIZE) {
    cb_.fn(ptr, PACKET_SIZE);
    ptr += PACKET_SIZE;
    temp_buffer_size_ -= PACKET_SIZE;
  }
  memmove(temp_buffer_, ptr, temp_buffer_size_);
}

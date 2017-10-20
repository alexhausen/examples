#pragma once

#include <cstdint>

class callback {
 public:
  virtual ~callback() {}
  virtual void fn(const uint8_t*, size_t) const = 0;
};

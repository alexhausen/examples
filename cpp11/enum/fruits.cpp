#include <stdexcept>
#include "fruits.h"

static const char* fruits_str[] = { "banana", "apple", "pinaple" };

FruitEnum::FruitEnum(fruit_enum f):Enum(f) {
}

void FruitEnum::set(const std::string& s) {
  for (size_t i = 0; i < 3; i++) {
    if (s == fruits_str[i]) {
      value_ = static_cast<fruit_enum>(i);
      return;
    }
  }
  throw std::runtime_error("Invalid fruit");
}

std::string FruitEnum::str() const {
  return fruits_str[static_cast<int>(get())];
}

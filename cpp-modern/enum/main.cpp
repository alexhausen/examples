#include <cassert>
#include <iostream>

#include "fruits.h"

int main() {
  FruitEnum fruit{fruit_enum::banana};
  fruit.set("apple");
  assert(fruit.get() == fruit_enum::apple);
  std::cout << fruit.str() << std::endl;
}

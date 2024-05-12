#include <iostream>
#include "log.h"

int main() {
  const char* c1 = "category1";
  const char* c2 = "category2";
  const char* c3 = "category3";

  log::add(c1);
  log::add(c2);
  log::add(c3);

  log::unblock("*");
  log::block(c2);

  for (const auto& i : log::ls()) {
    std::cout << i.first << " : " << std::boolalpha << i.second << std::endl;
  }

  LOG_BASIC(log::level::debug, c1) << std::endl;
  LOG_D(c1) << "message 1 0x" << std::hex << 255 << std::endl;
  LOG_I(c1) << "message 2 " << 255 << std::endl;
  LOG_W(c1) << "message 3" << std::endl;
  LOG_D(c2) << "should not display" << std::endl;
  LOG_E(c3) << "message 4" << std::endl;
  log::set_level(log::level::warning);
  LOG_I(c1) << "should not display" << std::endl;

}

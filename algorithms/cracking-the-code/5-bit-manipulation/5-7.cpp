/*
5.7
Pairwise Swap: Write a program to swap odd and even bits in an integer with as 
few instructions as possible (e.g., bit 0 and bit 1 are swapped, bit 2 and bit 
3 are swapped, and so on).
Hints: #145, #248, #328, #355
*/

#include <cassert>
#include <iostream>

unsigned swap_odd_even_bits(unsigned x) {
  constexpr unsigned mask_odd_bits = 0x5555'5555u;
  constexpr unsigned mask_even_bits = 0xAAAA'AAAAu;
  unsigned x_odd_bits = (x & mask_odd_bits);
  unsigned x_even_bits = (x & mask_even_bits);
  return (x_odd_bits << 1) | (x_even_bits >> 1);
}

int main() {
  assert(swap_odd_even_bits(0) == 0);
  assert(swap_odd_even_bits(1) == 2);
  assert(swap_odd_even_bits(2) == 1);
  assert(swap_odd_even_bits(3) == 3);
  assert(swap_odd_even_bits(0xAAAAu) == 0x5555u);
  assert(swap_odd_even_bits(0x5555u) == 0xAAAAu);
  assert(swap_odd_even_bits(0x7654'3210) == 0xB9A8'3120);
  assert(swap_odd_even_bits(0xFEDC'BA98) == 0xFDEC'7564);

  std::cout << "OK" << std::endl;
}

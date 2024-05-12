/*
5.1
Insertion: You are given two 32-bit numbers, N and M, and two bit positions, i and
j. Write a method to insert M into N such that M starts at bit j and ends at bit i. You
can assume that the bits j through i have enough space to fit all of M. That is, if
M = 10011, you can assume that there are at least 5 bits between j and i. You would not, for
example, have j = 3 and i = 2, because M could not fully fit between bit 3 and bit 2.
EXAMPLE
Input:  N = 10000000000, M = 10011, i = 2, j = 6
Output: N = 10001001100

Hints: #137, #169, #215
*/

#include <cassert>
#include <iostream>

u_int32_t bit_insert(u_int32_t n, u_int32_t m, u_int32_t i, u_int32_t j) {
  u_int32_t mask_i = (~0u) << i;
  u_int32_t mask_j = (~0u) << (j+1);
  u_int32_t mask = mask_i & ~mask_j;
  u_int32_t m2 = (m << i) & mask;
  return n | m2;
}

int main() {

  u_int32_t a = 0b0100'0000'0000u;
  u_int32_t b = 0b0000'0001'0011u;
  u_int32_t c = 0b0100'0100'1100u;

  assert(bit_insert(a, b, 2, 6) == c);

  std::cout << "OK" << std::endl;
}

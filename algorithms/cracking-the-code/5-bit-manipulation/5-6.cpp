/*
5.6
Conversion: Write a function to determine the number of bits you would need to flip to 
convert integer A to integer B.
EXAMPLE
Input:29 (or: 11101), 15 (or: 01111)
Output:2
Hints: #336, #369
*/

#include <cassert>
#include <iostream>

int f(int a, int b) {
  int n = 0;
  /*
  // Good, but can be improved
  for (int c = a ^ b; c != 0; c >>= 1) {
    n += c & 1;
  }
  */

  // The operation c = c & (c-1) will clear the least significant bit in c.
  for (int c = a ^ b; c != 0; c = c & (c - 1)) {
    n++;
  }
  return n;
}

int main() {
  int r0 = f(0, 0);
  assert(r0 == 0);

  int r1 = f(29, 15);
  assert(r1 == 2);

  int r2 = f(2, 1);
  assert(r2 == 2);

  int r3 = f(3, 1);
  assert(r3 == 1);

  std::cout << "OK" << std::endl;
}

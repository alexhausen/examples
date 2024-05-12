/*
5.3
Flip Bit to Win: You have an integer and you can flip exactly one bit from a 0 to a 1.
Write code to find the length of the longest sequence of 1s you could create.
EXAMPLE
Input: 1775 (or: 11011101111)
Output: 8
Hints: #159, #226, #314,#352
*/

#include <cassert>
#include <iostream>

int flip(u_int32_t a) {
  //special case, all bits are already set
  if (~a == 0u) {
    return 32;
  }
  int current_len = 0;
  int previous_len = 0;
  int max_len = 1;
  while (a != 0) {

    // current bit is 1
    if ((a & 1) == 1) {
      current_len++;
    
    // current bit is 0
    } else {
      // if next bit is also a 0 don't merge lenghts
      previous_len = (a & 2u) == 0u ? 0 : current_len;
      // gap, reset current_len
      current_len = 0;
    }
    // + 1 considers the flip of the next bit
    max_len = std::max(previous_len + current_len + 1, max_len);
    a = a >> 1;
  }
  return max_len;
}

int main() {

  u_int32_t input = 0b0110'1110'1111;

  assert(flip(input) == 8);

  std::cout << "OK" << std::endl;
}

/*
8.5
Recursive Multiply: Write a recursive function to multiply two positive integers without using the
*operator.You can use addition, subtraction, and bit shifting, but you should minimize the number
of those operations.
Hints: #166, #203, #227, #234, #246, #280
*/

#include <cassert>
#include <iostream>

using namespace std;

// naive O(a)
/*
int mult(int a, int b) {
  if (a == 0 || b == 0) return 0;
  if (a == 1) return b;
  return mult(a - 1, b) + b;
}
*/

// O(log small)
int mult_(int small, int big) {
  if (small == 0) return 0;
  if (big == 1) return big;
  int half = small >> 1; // div by 2
  int half_mult = mult_(half, big);
  bool even = small % 2 == 0;
  if (even) {
    return half_mult + half_mult;
  } else {
    return half_mult + half_mult + big;
  }
}

int mult(int a, int b) {
  int small = min(a, b);
  int big = max(a, b);
  return mult_(small, big);
}


int main() {
  
  int r0 = mult(0, 2);
  assert(r0 == 0);

  int r1 = mult(1, 2);
  assert(r1 == 2);

  int r2 = mult(3, 4);
  assert(r2 == 12);

  cout << "OK" << endl;
}

/*
5.4
Next Number: Given a positive integer, print the next smallest and the next 
largest number that have the same number of 1 bits in their binary representation.
Hints: #147, #175, #242, #312, #339, #358, #375, #390
*/

#include <cassert>
#include <iostream>
#include <limits>

unsigned number_of_1s(unsigned n) {
  unsigned ones = 0;
  while (n > 0) {
    ones += (n & 1);
    n >>= 1;
  }
  return ones;
}

bool same_number_of_1s(unsigned a, unsigned b) {
  return number_of_1s(a) == number_of_1s(b);
}

// brute force
std::pair<unsigned, unsigned> next_pair(unsigned n) {
  unsigned smallest = n;
  unsigned largest = n;
  while (smallest > 0) {
    smallest--;
    if (same_number_of_1s(smallest, n)) {
      break;
    }
  }
  while (largest < std::numeric_limits<unsigned>::max()) {
    largest++;
    if (same_number_of_1s(largest, n)) {
      break;
    }
  }
  return {smallest, largest};
}

int main() {
  
  std::pair<unsigned, unsigned> expected1 = {1, 4};
  assert(expected1 == next_pair(2));

  std::pair<unsigned, unsigned> expected2 = {5, 9};
  assert(expected2 == next_pair(6));

  std::cout << "OK" << std::endl;
}

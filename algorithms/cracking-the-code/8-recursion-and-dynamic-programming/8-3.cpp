/*
8.3
Magic Index: A magic index in an array A [0...n-1] is defined to be an index 
such that A[i] = i. Given a sorted array of distinct integers, write a method 
to find a magic index, if one exists, in array A.
FOLLOW UP
What if the values are not distinct?
Hints: #170, #204, #240, #286, #340
*/

#include <cassert>
#include <iostream>
#include <vector>

// binary search-like algorithm
// Time complexity: O(log N)
int magic_(const std::vector<int>& a, int lower, int upper) {
  if (upper < lower) {
    return -1;
  }
  int i = lower + (upper - lower) / 2; 
  if (a[i] == i) {
    return i;
  }
  if (a[i] < i) {
    lower = i + 1;
  } else {
    upper = i - 1;
  }
  return magic_(a, lower, upper);
}

int magic(const std::vector<int>& a) {
  /*
  // brute force algorithm O(N)
  int a_size = static_cast<int>(a.size());
  for (int i = 0; i < a_size; ++i) {
    if (a[i] == i) {
      return i;
    }
  }
  */
  return magic_(a, 0, a.size()-1);
}

// follow-up question
int magic2_(const std::vector<int>& a, int lower, int upper) {
  if (upper < lower) {
    return -1;
  }
  int i = lower + (upper - lower) / 2; 
  int value = a[i];
  if (value == i) {
    return i;
  }

  // Because we can have repetitions we must search both sides
  // But since they are sorted, we can skip those indexes that not possible
  // to contain the magic value

  // search left
  int left_i = std::min(i - 1, value);
  int left = magic2_(a, lower, left_i);
  if (left >= 0) {
    return left;
  }

  // search right
  int right_i = std::max(i + 1, value);
  int right = magic2_(a, right_i, upper);
  return right;
}

int magic2(const std::vector<int>& a) {
  return magic2_(a, 0, a.size()-1);
}

int main() {

  std::vector<int> v1 = { 0, 2, 3 };
  std::vector<int> v2 = { 1, 2, 3 };

  assert(magic(v1) == 0);
  assert(magic(v2) == -1);

  std::vector<int> v3 = { -10, -5, -1, 1, 2, 3, 5, 7, 9, 12, 13 };
  assert(magic(v3) == 7);
  
  // follow-up question
  std::vector<int> v4 = { -10, -5, 2, 2, 2, 3, 5, 7, 9, 12, 13 };
  assert(magic2(v4) == 2);

  std::cout << "OK" << std::endl;
}

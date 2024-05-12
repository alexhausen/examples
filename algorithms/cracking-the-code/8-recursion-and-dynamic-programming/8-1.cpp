/*
8.1
Triple Step: A child is running up a staircase with n steps and can hop either
1 step, 2 steps, or 3 steps at a time. Implement a method to count how many
possible ways the child can run up the stairs.
Hints: #152, #178, #217, #237, #262, #359
*/

#include <cassert>
#include <iostream>

int memo[100] = {0};

// Time complexity: O(n)
// Space complexity: O(n), recursive solution
// Time complexity without memoization: O(3^n)
int count_ways(int n) {
  if (n < 0) {
    return 0;
  }
  if (n == 0) {
    return 1;
  }
  if (n < 100 && memo[n] != 0) {
    return memo[n];
  }
  int count = count_ways(n - 1) + count_ways(n - 2) + count_ways(n - 3);
  if (n < 100) {
    memo[n] = count;
  }
  return count;
}

int main() {
  assert(count_ways(1) == 1);
  assert(count_ways(2) == 2);
  assert(count_ways(3) == 4);

  std::cout << "OK" << std::endl;
}

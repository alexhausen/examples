/*
8.11
Coins: Given an infinite number of quarters (25 cents), dimes (10 cents),
nickels (5 cents), and pennies (1 cent), write code to calculate the number
of ways of representing n cents.
Hints: #300, #324, #343, #380, #394
*/

#include <array>
#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

using Coins = array<unsigned, 4>;
using Cache = unordered_map<unsigned, Coins>;

int change_(unsigned amount, const Coins& coins, unsigned index, Cache& cache) {
  unsigned cached_value = cache[amount][index];
  if (cached_value != 0) {
    return cached_value;
  }
  if (index == coins.size() - 1) {
    return 1; // it's always possible to represent a value using only pennies
  }
  int coin = coins[index];
  int ways = 0;
  for (unsigned i = 0; i * coin <= amount; i++) {
    int remaining = amount - (i * coin);
    ways += change_(remaining, coins, index + 1, cache);
  }
  cache[amount][index] = ways;
  return ways;
}

int change(int n) {
  Cache cache;
  Coins coins = {25, 10, 5, 1};
  return change_(n, coins, 0, cache);
}

int main() {

  assert(change(1) == 1);
  assert(change(6) == 2);

  cout << "OK" << endl;
}

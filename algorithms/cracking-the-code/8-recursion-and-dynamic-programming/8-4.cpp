/*
8.4
Power Set: Write a method to return all subsets of a set.
Hints: #273, #290, #338, #354, #373
*/

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> get_subsets(const vector<int>& s, unsigned index) {
  vector<vector<int>> ss;
  if (s.size() == index) {
    return {{}};
  }
  ss = get_subsets(s, index + 1);
  int x = s[index];
  vector<vector<int>> more_ss;
  for (const auto& temp : ss) {
    vector<int> new_subset(temp.begin(), temp.end());
    new_subset.push_back(x);
    more_ss.push_back(new_subset);
  }
  // append ss + more
  for (const auto& temp : more_ss) {
    ss.push_back(temp);
  }
  return ss;
}

int main() {
  auto ss1 = get_subsets({}, 0);
  vector<vector<int>> expected1 = {{}};
  assert(ss1 == expected1);

  vector<int> input2 = {1, 2};
  auto ss2 = get_subsets(input2, 0);
  vector<vector<int>> expected2 = { {}, {2}, {1}, {2, 1}};
  assert(ss2 == expected2);

  vector<int> input3 = {1, 2, 3};
  auto ss3 = get_subsets(input3, 0);
  vector<vector<int>> expected3 = { {}, {3}, {2}, {3, 2}, {1}, {3, 1}, {2, 1}, {3, 2, 1}};
  assert(ss3 == expected3);

  cout << "OK" << endl;
}

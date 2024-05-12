/*
8.9
Parens: Implement an algorithm to print all valid (e.g., properly opened and
closed) combinations of n pairs of parentheses.
EXAMPLE
Input: 3
Output: ((())) , (()()) , (())() , ()(()) , ()()()
Hints: #138, #174, #187, #209, #243, #265, #295
*/

#include <cassert>
#include <iostream>
#include <set>
#include <string>

using namespace std;

// O(n), 2*n calls
void add_parenthesis(set<string>& ss, int left, int right, const string& str) {
  // check invalid state
  if (left < 0 ||   // no more ( to add
      right < left  // must have ) to add for each (
                    // || right < 0 condition is implied by the previous conditions
  ) {
    return;
  }

  // done, no more left or right parenthesis to add
  if (left == 0 && right == 0) {
    ss.insert(str);
    return;
  }

  add_parenthesis(ss, left - 1, right, str + "(");
  add_parenthesis(ss, left, right - 1, str + ")");
}

set<string> gen_parenthesis(int n) {
  set<string> ss;
  string str;
  add_parenthesis(ss, n, n, str);
  return ss;
}

int main() {
  set<string> expected0 = {""};
  assert(gen_parenthesis(0) == expected0);

  set<string> expected1 = {"()"};
  assert(gen_parenthesis(1) == expected1);

  set<string> expected2 = {"(())", "()()"};
  assert(gen_parenthesis(2) == expected2);

  set<string> expected3 = {"((()))", "(()())", "(())()", "()(())", "()()()"};
  assert(gen_parenthesis(3) == expected3);

  cout << "OK" << endl;
}

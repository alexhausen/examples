/*
8.14
Boolean Evaluation: Given a boolean expression consisting of the symbols
0 (false), 1 (true), & (AND), I (OR), and /\ (XOR), and a desired boolean
result value result, implement a function to count the number of ways of
parenthesizing the expression such that it evaluates to result.
EXAMPLE
countEval("1^0|0|1", false) -> 2
countEval("0&0&0&1^1|0", true) -> 10
Hints: #148, #168, #197, #305, #327
*/

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

int count_eval(const string& s, bool expected) {
  if (s.size() == 0) {
    return 0;
  }
  if (s.size() == 1) {
    bool bit = s[0] == '1';
    return expected == bit;
  }

  int ways = 0;
  for (unsigned i = 1; i < s.size(); i += 2) {
    // char op = s[i];
    // string left = s.substr(0, i);
    // string right = s.substr(i + 1);

    // int left_true = count_eval(left, true);
    // int left_false = count_eval(left, false);
    // int right_true = count_eval(right, true);
    // int right_false = count_eval(right, false);

    // int total = (left_true + left_false) * (right_true + right_false);

    // int total_true = 0;
    // if (op == '^') {
    //   total_true = left_true * right_false + left_false * right_true;
    // } else if (op == '&') {
    //   total_true = left_true * right_true;
    // } else if (op == '|') {
    //   total_true = 
    //     left_true * right_true + 
    //     left_false * right_true +
    //     left_false * right_true;
    // }
    // int total_false = total - total_true;
    // int sub_ways = expected ? total_true : total_false;
    // ways += sub_ways;
  }
  return ways;
}

int main() {
  int r0 = count_eval("1|0", true);
  assert(r0 == 1);

  int r1 = count_eval("1^0|0|1", false);
  assert(r1 == 2);

  int r2 = count_eval("0&0&0&1^1|0", true);
  assert(r2 == 10);

  cout << "OK" << endl;
}

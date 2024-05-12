/*
8.7
Permutations without Dups: Write a method to compute all permutations of a 
string of unique characters.
Hints:#150, #185, #200, #267, #278, #309, #335, #356
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> permutations(const string& input) {
  if (input.empty()) {
    return {""};
  }
  vector<string> perms;
  // remove the unique char from string
  char ch = input[0];
  string rest = input.substr(1);
  vector<string> words = permutations(rest);
  for (const string& word: words) {
    // place it in all possible positions
    for (auto i = 0u; i <= word.size(); ++i) {
      string s = word;
      s.insert(i, 1, ch);
      perms.push_back(s);
    }
  }
  return perms;
}

int main() {

  vector<string> expected0 = {""};
  assert(permutations("") == expected0);
  
  vector<string> expected1 = {"a"};
  assert(permutations("a") == expected1);

  vector<string> expected2 = {"ab", "ba"};
  assert(permutations("ab") == expected2);

  vector<string> expected3 = {"abc", "bac", "bca", "acb", "cab", "cba"};
  assert(permutations("abc") == expected3);

  cout << "OK" << endl;
}

/*
8.8
Permutations with Dups: Write a method to compute all permutations of a string 
whose charac­ters are not necessarily unique. The list of permutations should 
not have duplicates.
Hints: #161, #190, #222, #255
*/

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

void permutations2(unordered_map<char, int>& hash, const string& prefix, int remaining, vector<string>& result) {
  if (remaining == 0) {
    result.push_back(prefix);
    return;
  }
  for (auto [ch, count]: hash) {
    if (count > 0) {
      hash[ch]--;
      permutations2(hash, prefix + ch, remaining - 1, result);
      hash[ch]++;
    }
  }
}

vector<string> permutations(const string& input) {
  vector<string> result;
  unordered_map<char, int> hash;
  for (char c: input) {
    hash[c]++;
  }
  permutations2(hash, "", input.size(), result);
  return result;
}

int main() {

  vector<string> expected0 = {""};
  assert(permutations("") == expected0);
  
  vector<string> expected1 = {"a"};
  assert(permutations("a") == expected1);

  vector<string> expected2 = {"ba", "ab"};
  assert(permutations("ab") == expected2);

  vector<string> expected3 = {"aa"};
  assert(permutations("aa") == expected3);

  vector<string> expected4 = {"aaa"};
  assert(permutations("aaa") == expected4);

  vector<string> expected5 = {"cba", "cab", "bca", "bac", "acb", "abc"};
  assert(permutations("abc") == expected5);

  vector<string> expected6 = {"baa", "aba", "aab"};
  assert(permutations("aba") == expected6);

  cout << "OK" << endl;
}

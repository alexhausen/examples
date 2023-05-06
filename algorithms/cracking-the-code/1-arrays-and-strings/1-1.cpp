/*
1.1
Is Unique: Implement an algorithm to determine if a string has all unique characters.
What if you cannot use additional data structures?
  A 1: array of 256 bool, each position is a char.
  A 2: sort and for each char is equal to previous char
Hints: #44, #117, #132
*/

#include <cassert>
#include <string>
#include <unordered_set>
#include <iostream>

bool is_unique(const std::string& input) {
    std::unordered_set<char> hash;
    for (char c : input) {
        if (hash.count(c) != 0) return false;
        hash.insert(c);
    }
    return true;
}

int main() {
    assert(is_unique("abc"));
    assert(!is_unique("abbc"));
    std::cout << "OK" << std::endl;
}

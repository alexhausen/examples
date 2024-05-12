/*
1.1
Is Unique: Implement (a) an algorithm to determine if a string has all unique characters.
(b) What if you cannot use additional data structures?
  A 1: array of 256 bool, each position is a char.
  A 2: sort and for each char is equal to previous char
Hints: #44, #117, #132
*/

#include <array>
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

// input has letters only
bool is_unique_no_additional_space(const std::string& input) {
    std::array<bool, 26> chars = {false};
    for (char c : input) {
        if (!std::isalpha(c)) {
            throw "invalid input";
        }
        int i = std::tolower(c) - 'a';
        if (chars[i]) return false;
        chars[i] = true;
    }
    return true;
}

int main() {
    assert(is_unique("abc"));
    assert(!is_unique("abbc"));

    assert(is_unique_no_additional_space("abc"));
    assert(!is_unique_no_additional_space("abbc"));

    std::cout << "OK" << std::endl;
}

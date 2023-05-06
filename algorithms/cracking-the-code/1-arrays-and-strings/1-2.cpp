/*
1.2
Check Permutation: Given two strings, write a method to decide if one is a permutation of the
other.
Hints: #1, #84, #122, #131
*/

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

bool check_permutation(const std::string& s1, const std::string& s2) {
    if (s1.size() != s2.size()) return false;
    std::unordered_map<char, int> mp;
    for (char c : s1) {
        mp[c]++;
    }
    for (char c : s2) {
        mp[c]--;
    }
    for (const auto& [k, v] : mp) {
        if (v != 0) return false;
    }
    return true;
}

int main() {
    assert(check_permutation("", ""));
    assert(!check_permutation("a", ""));
    assert(!check_permutation("", "a"));
    assert(!check_permutation("abb", "bac"));
    assert(check_permutation("a", "a"));
    assert(check_permutation("abcd", "cbad"));
    std::cout << "OK" << std::endl;
}

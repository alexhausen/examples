/*
1.5
One Away: There are three types of edits that can be performed on strings: insert a character,
remove a character, or replace a character. Given two strings, write a function to check if they are
one edit (or zero edits) away.
EXAMPLE
pale,  ple  -> true
pales, pale -> true
pale,  bale -> true
pale,  bake -> false
Hints:#23, #97, #130
*/

#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

bool one_away(const std::string& s1, const std::string& s2) {
    std::unordered_map<char, int> hash;
    for (char c : s1) {
        hash[c]++;
    }
    for (char c : s2) {
        hash[c]--;
    }
    int inserts = 0;
    int removes = 0;
    for (const auto& [k, v] : hash) {
        if (v > 0)
            inserts++;
        if (v < 0)
            removes++;
    }
    return (inserts == 0 && removes == 0) ||  // 0 edit
           (inserts == 1 || removes == 1);    // 1 edit
}

int main() {
    assert(one_away("", ""));
    assert(one_away("", "a"));
    assert(one_away("a", ""));
    assert(one_away("pale", "ple"));
    assert(one_away("pale", "pales"));
    assert(one_away("pales", "pale"));
    assert(one_away("pale", "bale"));
    assert(one_away("pale", "bake") == false);
    std::cout << "OK" << std::endl;
}

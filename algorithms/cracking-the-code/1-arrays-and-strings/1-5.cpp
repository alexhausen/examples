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

bool one_replace_away(const std::string& s1, const std::string& s2) {
    auto n = s1.size();
    int diff_count = 0;
    for (auto i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            if (diff_count > 0) {
                return false;
            }
            diff_count++;
        }
    }
    return true;
}

bool one_insert_away(const std::string& s1, const std::string& s2) {
    unsigned i1 = 0;
    unsigned i2 = 0;
    while (i1 < s1.size() && i2 < s2.size()) {
        if (s1[i1] != s2[i2]) {
            bool already_skipped_once = i1 != i2;            
            if (already_skipped_once) {
                return false;
            }
            i2++; // skip
        } else {
            i1++;
            i2++;
        }
    }
    return true;
}

bool one_edit_away(const std::string& s1, const std::string& s2) {
    if (s1.size() == s2.size()) {
        return one_replace_away(s1, s2);
    } else if (s1.size() + 1 == s2.size()) {
        return one_insert_away(s1, s2);
    } else if (s1.size() - 1 == s2.size()) {
        return one_insert_away(s2, s1);
    }
    return false;
}

int main() {
    assert(one_edit_away("", ""));
    assert(one_edit_away("", "a"));
    assert(one_edit_away("a", ""));
    assert(one_edit_away("pale", "ple"));
    assert(one_edit_away("pale", "pales"));
    assert(one_edit_away("pales", "pale"));
    assert(one_edit_away("pale", "bale"));
    assert(one_edit_away("pale", "bake") == false);
    assert(one_edit_away("pale", "bae") == false);
    std::cout << "OK" << std::endl;
}

/*
1.9
String Rotation: Assumeyou have a method isSubstring which checks if one word is a substring
of another. Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only
one call to isSubstring (e.g.,"waterbottle" is a rotation of "erbottlewat").
Hints: #34, #88, #104
*/

#include <cassert>
#include <iostream>
#include <string>

// is sub a substring of str?
bool is_substring(const std::string& sub, const std::string& str) {
    return str.find(sub, 0) != std::string::npos;
}

bool is_rotation(const std::string& s1, const std::string& s2) {
    if (s1.size() != s2.size())
        return false;

    const unsigned n = s1.size();
    unsigned p1 = 0;
    unsigned p2 = 0;
    bool saved = true;
    for (unsigned i = 0; i < n; i++) {
        if (s2[i] == s1[p1]) {
            if (!saved) {
                saved = true;
                p2 = i;
            }
            p1++;
        } else {
            p1 = 0;
            saved = false;
        }
    }
    if (saved) {
        unsigned count = n - (n - p2);
        std::string sub{s2, 0, count};
        return is_substring(sub, s1);
    }
    return false;
}

int main() {
    assert(is_substring("", ""));
    assert(is_substring("a", "ab"));
    assert(is_substring("ab", "ab"));
    assert(is_substring("ab", "cab"));
    assert(!is_substring("ab", "a"));

    assert(is_rotation("", ""));
    assert(is_rotation("abc", "abc"));
    assert(is_rotation("cab", "abc"));
    assert(is_rotation("waterbottle", "erbottlewat"));
    assert(is_rotation("abcabd", "bdabca"));
    assert(is_rotation("acb", "abc") == false);
}

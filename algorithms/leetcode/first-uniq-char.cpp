// https://leetcode.com/explore/learn/card/hash-table/184/comparison-with-other-data-structures/1120/
/*
Given a string s, find the first non-repeating character in it and return its index.
If it does not exist, return -1.
Constraints:
    1 <= s.length <= 105
    s consists of only lowercase English letters.
*/

#include <cassert>

#include <string>
#include <unordered_map>

// With a hash map
// Time complexity: O(N)
// Space complexity: O(N)
int firstUniqChar(const std::string& s) {
    std::unordered_map<char, int> hash;
    for (auto i = 0u; i < s.length(); ++i) {
        char c = s[i];
        if (hash.count(c) == 0) {
            hash[c] = 1;
        } else {
            hash[c] = 2;
        }
    }
    for (auto i = 0u; i < s.length(); ++i) {
        char c = s[i];
        if (hash[c] == 1) {
            return i;
        }
    }
    return -1;
}

// Without a hash map
// Time complexity: O(N)
// Space complexity: O(1)
int firstUniqChar2(const std::string& s) {
    int count_chars[26] = {0};
    for (char c: s) {
        count_chars[c - 'a']++;
    }
    for (auto i = 0u; i < s.length(); ++i) {
        char c = s[i];
        if (count_chars[c - 'a'] == 1) {
            return i;
        }
    }
    return -1;
}

int main() {
    assert(firstUniqChar("leetcode") == 0);
    assert(firstUniqChar("loveleetcode") == 2);
    assert(firstUniqChar("aabb") == -1);

    assert(firstUniqChar2("leetcode") == 0);
    assert(firstUniqChar2("loveleetcode") == 2);
    assert(firstUniqChar2("aabb") == -1);
}

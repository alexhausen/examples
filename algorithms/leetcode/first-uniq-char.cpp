// https://leetcode.com/explore/learn/card/hash-table/184/comparison-with-other-data-structures/1120/

#include <cassert>
#include <string>
#include <unordered_map>

int firstUniqChar(const std::string& s) {
    std::unordered_map<char, int> hash;
    for (int i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (hash.count(c) == 0) {
            hash[c] = 1;
        } else {
            hash[c] = 2;
        }
    }
    for (int i = 0; i < s.length(); ++i) {
        char c = s[i];
        if (hash[c] == 1) {
            return i;
        }
    }
    return -1;
}

int main() {
    assert(firstUniqChar("leetcode") == 0);
    assert(firstUniqChar("loveleetcode") == 2);
    assert(firstUniqChar("aabb") == -1);
}

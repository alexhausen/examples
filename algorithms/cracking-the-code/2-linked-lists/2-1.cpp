/*
2.1
Remove Dups! Write code to remove duplicates from an unsorted linked list.
FOLLOW UP
How would you solve this problem if a temporary buffer is not allowed?
Hints: #9, #40
*/

#include <cassert>
#include <iostream>
#include <list>
#include <unordered_set>

// O(n) time, O(m) space
void remove_dups(std::list<int>& l) {
    std::unordered_set<int> hash;
    auto it = l.begin();
    while (it != l.end()) {
        if (hash.count(*it) == 0) {
            hash.insert(*it);
            ++it;
        } else {;
            it = l.erase(it);
        }
    }
}

// O(n^2) time, O(1) space
void remove_dups_inplace(std::list<int>& l) {
    for (auto it1 = l.begin(); it1 != l.end(); ++it1) {
        auto it2 = it1;
        ++it2;
        while (it2 != l.end()) {
            if (*it1 != *it2) {
                ++it2;
            } else {
                it2 = l.erase(it2);
            }
        }
    }
}

int main() {
    std::list<int> l1 = {42, 10, 11, 42, 13, 11};
    const std::list<int> expected_l1 = {42, 10, 11, 13};
    remove_dups(l1);
    assert(l1 == expected_l1);

    std::list<int> l2 = {42, 10, 11, 42, 13, 11};
    const std::list<int> expected_l2 = {42, 10, 11, 13};
    remove_dups_inplace(l2);
    assert(l2 == expected_l2);

    std::cout << "OK" << std::endl;
}

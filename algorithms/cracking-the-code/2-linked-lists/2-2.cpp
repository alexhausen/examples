/*
2.1
Return Kth to Last: Implement an algorithm to find the kth to last element of a singly linked list.
Hints:#8, #25, #41, #67, #126
*/

#include <cassert>
#include <forward_list>
#include <iostream>

int find_kth_to_last(const std::forward_list<int>& l, int k) {
    assert(k > 0);
    auto it1 = l.cbegin();
    for (int i = 0; i < k - 1; i++) {
        assert(it1 != l.cend());
        ++it1;
    }
    for (auto it2 = l.cbegin(); it2 != l.cend(); ++it2) {
        ++it1;
        if (it1 == l.cend()) {
            return *it2;
        }
    }
    throw "error";
}

int main() {

    std::forward_list<int> l1 = { 4, 9, 33, 12, 1, 90 };
    assert(find_kth_to_last(l1, 3) == 12);
    assert(find_kth_to_last(l1, 6) == 4);
    assert(find_kth_to_last(l1, 1) == 90);

    std::cout << "OK" << std::endl;
}

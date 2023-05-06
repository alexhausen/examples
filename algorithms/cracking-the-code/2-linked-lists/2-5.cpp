/*
2.5
Sum Lists: You have two numbers represented by a linked list, where each node contains a single
digit. The digits are stored in reverse order, such that the 1 's digit is at the head of the list.
Write a function that adds the two numbers and returns the sum as a linked list.
EXAMPLE
Input: (7 -> 1 -> 6) + (5 -> 9 -> 2). That is, 617 + 295.
Output: 2 -> 1 -> 9. That is, 912.
FOLLOW UP
Suppose the digits are stored in forward order. Repeat the above problem.
EXAMPLE
Input: (6 -> 1 -> 7) + (2 -> 9 -> 5). That is, 617 + 295.
Output: 9 -> 1 -> 2. That is, 912.
Hints: #7, #30, #71, #95, #109
*/

#include <cassert>
#include <iostream>
#include <list>

std::list<int> sum_lists(const std::list<int>& l1, const std::list<int>& l2) {
    std::list<int> l;
    auto it1 = l1.begin();
    auto it2 = l2.begin();
    int carry = 0;
    while (it1 != l1.end() || it2 != l2.end()) {
        if (it1 != l1.end() && it2 != l2.end()) {
            int sum = *it1 + *it2 + carry;
            carry = sum >= 10 ? 1 : 0;
            sum = sum % 10;
            l.push_back(sum);
            ++it1;
            ++it2;
        } else if (it1 != l1.end()) {
            int sum = *it1 + carry;
            carry = sum >= 10 ? 1 : 0;
            sum = sum % 10;
            l.push_back(*it1);
            ++it1;
        } else {
            int sum = *it2 + carry;
            carry = sum >= 10 ? 1 : 0;
            sum = sum % 10;
            l.push_back(*it2);
            ++it2;
        }
    }
    if (carry) {
        l.push_back(1);
    }
    return l;
}

int sum_lists_rec(std::list<int>::const_iterator it1,
                  std::list<int>::const_iterator end1,
                  std::list<int>::const_iterator it2,
                  std::list<int>::const_iterator end2,
                  std::list<int>& result) {
    if (it1 == end1 || it2 == end2) {
        return 0;
    }
    int value1 = *it1;
    int value2 = *it2;
    int carry = sum_lists_rec(++it1, end1, ++it2, end2, result);
    int sum = value1 + value2 + carry;
    carry = sum >= 10 ? 1 : 0;
    sum = sum % 10;
    result.push_front(sum);
    return carry;
}

std::list<int> sum_lists_in_order(const std::list<int>& l1, const std::list<int>& l2) {
    std::list<int> ol1{l1};
    std::list<int> ol2{l2};
    unsigned size1 = ol1.size();
    unsigned size2 = ol2.size();
    if (size1 > size2) {
        unsigned diff = size1 - size2;
        for (unsigned i = 0; i < diff; i++) {
            ol2.push_front(0);
        }
    } else if (size2 > size1) {
        unsigned diff = size2 - size1;
        for (unsigned i = 0; i < diff; i++) {
            ol1.push_front(0);
        }
    }
    std::list<int> result;
    int carry = sum_lists_rec(ol1.begin(), ol1.end(), ol2.begin(), ol2.end(), result);
    if (carry) {
        result.push_front(1);
    }
    return result;
}

int main() {
    const std::list<int> l1 = {7, 1, 6};            // 617
    const std::list<int> l2 = {5, 9, 2};            // 295
    const std::list<int> expected_sum = {2, 1, 9};  // 912
    assert(sum_lists(l1, l2) == expected_sum);

    // follow up
    const std::list<int> ol1 = {7};
    const std::list<int> ol2 = {2, 9, 5};
    const std::list<int> expected_in_order = {3, 0, 2};
    assert(sum_lists_in_order(ol1, ol2) == expected_in_order);

    std::cout << "OK" << std::endl;
}

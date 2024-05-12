/*
2.4
Partition: Write code to partition a linked list around a value x, such that all nodes less than x
come before all nodes greater than or equal to x. If x is contained within the list, the values of x
only need to be after the elements less than x (see below). The partition element x can appear
anywhere in the "right partition"; it does not need to appear between the left and right partitions.
EXAMPLE
Input:  3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition= 5]
Output: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
Hints: #3, #24
*/

#include <cassert>
#include <iostream>
#include <list>

using list = std::list<int>;

// unstable
list partition(const list& l, int value) {
    list part_list;
    for (auto it = l.cbegin(); it != l.cend(); ++it) {
        if (*it < value) {
            part_list.push_front(*it);
        } else {
            part_list.push_back(*it);
        }
    }
    return part_list;
}

// stable: create 2 lists and concatenate them at the end
list stable_partition(const list& l, int value) {
    list l1;
    list l2;
    for (auto it = l.begin(); it != l.end(); ++it) {
        if (*it < value) {
            l1.push_back(*it);
        } else {
            l2.push_back(*it);
        }
    }
    l2.splice(l2.begin(), l1);
    return l2;
}

int main() {
    list list1 {3, 5, 8, 5, 10, 2, 1};
    list part_list1 = partition(list1, 5);
    assert(list1.size() == part_list1.size());
    list expected_list1 {1, 2, 3, 5, 8, 5, 10};
    assert(part_list1 == expected_list1);

    list list2 {3, 5, 8, 5, 10, 2, 1};
    list part_list2 = stable_partition(list2, 5);
    assert(list2.size() == part_list2.size());
    list expected_list2 {3, 2, 1, 5, 8, 5, 10};

    std::cout << "OK" << std::endl;
}

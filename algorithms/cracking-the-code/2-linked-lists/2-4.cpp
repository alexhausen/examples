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

struct node {
    node* next;
    node* previous;
    int data;

    node(int data) : next{nullptr}, previous{nullptr}, data{data} {}

    void append_to_tail(int data) {
        node* new_node = new node(data);
        node* temp = this;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_node;
        new_node->previous = temp;
    }
};

struct list {
    node* head;

    list() : head{nullptr} {}

    void append(int data) {
        if (head == nullptr) {
            head = new node(data);
        } else {
            head->append_to_tail(data);
        }
    }
};

bool equals(const list& l1, const list& l2) {
    const node* n1 = l1.head;
    const node* n2 = l2.head;
    if (n1 == nullptr && n2 == nullptr)
        return true;
    if (n1 == nullptr || n2 == nullptr)
        return false;
    while (n1 != nullptr && n2 != nullptr) {
        if (n1->data != n2->data)
            return false;
        n1 = n1->next;
        n2 = n2->next;
    }
    return n1 == n2;
}

void partition(list& l, int value) {
    node* pivot = l.head;
    while (pivot != nullptr) {
        if (pivot->data == value)
            break;
        pivot = pivot->next;
    }
    if (pivot == nullptr)
        return;
    // if pivot == head?
    node* n = l.head;
    while (n != nullptr) {
        node* next = n->next;
        node* previous = n->previous;
        if (n->data < value) {
            n->next = l.head->next;
            n->previous = nullptr;
            l.head = n;
            if (previous)
                previous->next = next;
            if (next && previous) //?
                next->previous = previous;
        }
        n = next;
    }
}

void assert_partition(const list& l, int value) {
    const node* n = l.head;
    while (n != nullptr && n->data < value) {
        n = n->next;
    }
    while (n != nullptr) {
        assert(n->data >= value);
        n = n->next;
    }
}

int main() {
    list list1;
    list1.append(3);
    list1.append(5);
    list1.append(8);
    list1.append(5);
    list1.append(10);
    list1.append(2);
    list1.append(1);

    partition(list1, 5);
    assert_partition(list1, 5);

    std::cout << "OK" << std::endl;
}

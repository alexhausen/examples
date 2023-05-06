/*
2.7
Intersection: Given two (singly) linked lists, determine if the two lists intersect. Return the
inter­ secting node. Note that the intersection is defined based on reference, not value. That is,
if the kth node of the first linked list is the exact same node (by reference) as the jth node of
the second linked list, then they are intersecting.
Hints: #20, #45, #55, #65, #76, #93, #111, #120, #129
*/

#include <cassert>
#include <iostream>

struct node {
    node* next;
    char data;

    node(char data) : next{nullptr}, data{data} {}

    void append(node* n) {
        node* temp = this;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = n;
    }
};

int size(const node* l) {
    int sz = 0;
    while (l != nullptr) {
        sz++;
        l = l->next;
    }
    return sz;
}

const node* intersection(const node* l1, const node* l2) {
    // O(A+B) time; O(1) space
    int size1 = size(l1);
    int size2 = size(l2);
    if (size1 > size2) {
        int diff = size1 - size2;
        for (int i = 0; i < diff; i++) {
            l1 = l1->next;
        }
    } else if (size2 > size1) {
        int diff = size2 - size1;
        for (int i = 0; i < diff; i++) {
            l2 = l2->next;
        }
    }
    while (l1 != nullptr && l2 != nullptr) {
        if (l1 == l2)
            return l1;
        l1 = l1->next;
        l2 = l2->next;
    }

    /*
    // O(n^2) time; O(1) space
    const node* n1 = l1;
    while (n1 != nullptr) {
        const node* n2 = l2;
        while (n2 != nullptr) {
            if (n1 == n2) return n1;
            n2 = n2->next;
        }
        n1 = n1->next;
    }
    */
    return nullptr;
}

int main() {
    node* a = new node('a');
    node* b = new node('b');
    node* c = new node('c');
    node* d = new node('d');
    node* e = new node('e');
    node* f = new node('f');
    node* g = new node('g');

    node* list1 = a;
    list1->append(b);
    list1->append(c);

    node* list2 = d;
    list2->append(e);
    list2->append(b);

    assert(intersection(list1, list2) == b);

    node* list3 = f;
    list3->append(g);

    assert(intersection(list1, list3) == nullptr);

    std::cout << "OK" << std::endl;
}

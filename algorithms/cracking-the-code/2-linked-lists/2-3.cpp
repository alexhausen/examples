/*
2.3
Delete Middle Node: Implement an algorithm to delete a node in the middle (i.e., any node but
the first and last node, not necessarily the exact middle) of a singly linked list, given only
access to that node.
EXAMPLE
Input: the node c from the linked list a->b->c->d->e->f
Result: nothing is returned, but the new linked list looks like a->b->d->e->f
Hints: #72
*/

#include <cassert>
#include <iostream>

struct node {
    node* next;
    char data;

    node(char data) : next{nullptr}, data{data} {}

    void append_to_tail(char data) {
        node* new_node = new node(data);
        node* temp = this;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
};

bool equals(const node* n1, const node* n2) {
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

void delete_middle(node* target) {
    assert(target != nullptr);
    assert(target->next != nullptr);
    target->data = target->next->data;
    node* temp = target->next;
    target->next = target->next->next;
    delete temp;
}

int main() {
    node list1{'a'};
    list1.append_to_tail('b');
    list1.append_to_tail('c');
    list1.append_to_tail('d');
    list1.append_to_tail('e');
    list1.append_to_tail('f');

    node expected_list1{'a'};
    expected_list1.append_to_tail('b');
    expected_list1.append_to_tail('d');
    expected_list1.append_to_tail('e');
    expected_list1.append_to_tail('f');

    node* c = list1.next->next;
    assert(c->data == 'c');

    delete_middle(c);
    assert(equals(&list1, &expected_list1));

    std::cout << "OK" << std::endl;
}

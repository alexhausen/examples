/*
2.8
Loop Detection: Given a circular linked list, implement an algorithm that returns the node at the
beginning of the loop.
DEFINITION
Circular linked list: A (corrupt) linked list in which a node's next pointer points to an earlier
node, so as to make a loop in the linked list.
EXAMPLE
Input: A -> B -> C -> D -> E -> C [the same C as earlier]
Output: C
Hints: #50, #69, #83, #90
*/

#include <cassert>
#include <iostream>

#include <unordered_set>

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

const node* find_loop(const node* n) {
    std::unordered_set<const node*> hash;
    while (n != nullptr) {
        if (hash.count(n) != 0) {
            return n;
        }
        hash.insert(n);
        n = n->next;
    }
    return nullptr;
}


int main() {

    node* a = new node('a');
    node* b = new node('b');
    node* c = new node('c');
    node* d = new node('d');
    node* e = new node('e');

    node* list = a;
    list->append(b);
    list->append(c);
    list->append(d);
    list->append(e);

    assert(find_loop(list) == nullptr);

    // create a loop
    e->next = c;
    assert(find_loop(list) == c);

    std::cout << "OK" << std::endl;
}

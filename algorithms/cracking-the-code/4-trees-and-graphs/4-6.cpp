/*
4.6
Successor: Write an algorithm to find the "next" node (i.e., in-order successor) of a given node in a
binary search tree. You may assume that each node has a link to its parent.
Hints: #79, #91
*/

#include <cassert>
#include <iostream>

struct Node {
  int value_;
  Node* left_;
  Node* right_;
  Node* parent_;

  Node(int value, Node* parent):value_{value}, left_{nullptr}, right_{nullptr}, parent_{parent} {};

};

struct BinarySearchTree {
  Node* root_;

  BinarySearchTree(): root_{nullptr} {}

  Node* Add(int value) {
    Node** n = &root_;
    Node* parent = nullptr;
    while (*n != nullptr) {
      parent = *n;
      n = value < (*n)->value_ ? &((*n)->left_) : &((*n)->right_);
    }
    *n = new Node(value, parent);
    return *n;
  }

};

const Node* left_most_node(const Node* n) {
  if (n == nullptr) return nullptr;
  if (n->left_ == nullptr) return n;
  return left_most_node(n->left_);
}

// The in-order-successor is the left-most node of the right node
// if it doesn't exist then we go up until the child is to the left
const Node* succ(const Node* n) {
  if (n == nullptr) return nullptr;
  if (n->right_) {
    return left_most_node(n->right_);
  }
  // go up until we came from the left instead of right
  const Node* q = n;
  const Node* p = q->parent_;
  while (p != nullptr && p->right_ == q) {
    q = p;
    p = p->parent_;
  }
  return p;
}

int main() {

  BinarySearchTree b0;
  assert(succ(b0.root_) == nullptr);

  BinarySearchTree b1;
  auto n10 = b1.Add(10);
  auto n5 = b1.Add(5);
  auto n4 = b1.Add(4);
  auto n3 = b1.Add(3);
  auto n9 = b1.Add(9);
  auto n6 = b1.Add(6);
  auto n7 = b1.Add(7);
  auto n11 = b1.Add(11);

  assert(succ(n10) == n11);
  assert(succ(n11) == nullptr);
  assert(succ(n6) == n7);
  assert(succ(n3) == n4);
  assert(succ(n4) == n5);
  assert(succ(n9) == n10);

  std::cout << "OK" << std::endl;
}

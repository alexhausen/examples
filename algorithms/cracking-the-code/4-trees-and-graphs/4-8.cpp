/*
4.8
First Common Ancestor: Design an algorithm and write code to find the first 
common ancestor of two nodes in a binary tree. Avoid storing additional nodes 
in a data structure.
NOTE: This is not necessarily a binary search tree.
Hints: #10, #16, #28, #36, #46, #70, #80, #96
*/

#include <cassert>
#include <iostream>

using namespace std;

struct Node {
  int value_;
  Node* left_;
  Node* right_;

  Node(int value): value_{value}, left_{nullptr}, right_{nullptr} {}
};

struct BinTree {
  Node* root_;
  BinTree(): root_{nullptr}{}
};

Node* add_node(Node** n, int value) {
  *n = new Node(value);
  return *n;
}

// First Common Ancestor
// note: requires both nodes to be part of the tree
Node* fca(Node* n, Node* p, Node* q) {
  if (n == nullptr) return nullptr;
  if (n == q && n == p) return n;

  auto l = fca(n->left_, p, q);
  if (l && l != p && l != q) {
    return l; // p or q found in the left sub-tree
  }
  
  auto r = fca(n->right_, p, q);
  if (r && r != l && r != q) {
    return r; // p or q found in the right sub-tree
  }

  if (l && r) {
    return n; // p and q found in different sub-trees, so this is the common ancestor
  } else if (n == p || n == q) {
    return n; // found node, return it
  } else {
    if (l) return l;
    if (r) return r;
  }
  return nullptr;
}

/*
// wrong!
Node* ancestor(Node* n, Node* x) {
  if (n == nullptr) {
    return nullptr;
  }
  if (n == x) {
    return n;
  }
  Node* left = ancestor(n->left_, x);
  if (left) {
    return left;
  } 
  Node* right = ancestor(n->right_, x);
  if (right) {
    return right;
  } 
  return nullptr;
}

Node* fca(Node* n, Node* p, Node* q) {
  if (n == nullptr) return nullptr;
  if (p == nullptr || q == nullptr) return nullptr;

  // post-order traversal
  auto l = fca(n->left_, p, q);
  if (l) return l;
  auto r = fca(n->right_, p, q);
  if (r) return r;

  auto left_p = ancestor(n->left_, p);
  auto left_q = ancestor(n->left_, q);
  if (left_p && left_q) {
    // both on the left sub-tree
    return n->left_;
  }
  auto right_p = ancestor(n->right_, p);
  auto right_q = ancestor(n->right_, q);
  if (right_p && right_q) {
    // both on the right sub-tree
    return n->right_;
  }
  if ((left_p && right_q) || (left_q && right_p)) {
    // nodes on different sides of the tree
    return n;
  }
  return nullptr;
}
*/

int main() {

  BinTree b;
  auto n1 = add_node(&b.root_, 1);
  auto n2 = add_node(&n1->left_, 2);
  auto n3 = add_node(&n1->right_, 3);
  auto n4 = add_node(&n2->left_, 4);
  auto n5 = add_node(&n2->right_, 5);
  auto n6 = add_node(&n3->left_, 6);
  auto n7 = add_node(&n4->left_, 7);
  assert(fca(b.root_, nullptr, nullptr) == nullptr);
  assert(fca(b.root_, n2, n3) == n1);
  assert(fca(b.root_, n2, n4) == n2);
  assert(fca(b.root_, n5, n6) == n1);
  assert(fca(b.root_, n7, n5) == n2);
  assert(fca(b.root_, n7, n7) == n7);
  assert(fca(b.root_, n1, n2) == n1);

  cout << "OK" << endl;
}

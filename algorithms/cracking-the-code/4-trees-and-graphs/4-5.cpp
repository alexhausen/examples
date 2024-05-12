/*
Validate BST: Implement a function to check if a binary tree is a binary search
tree. Hints: #35, #57, #86, #113, #128
*/

#include <cassert>
#include <iostream>

struct BinTreeNode {
  BinTreeNode(int value) : value_{value}, left_{nullptr}, right_{nullptr} {}

  int value_;
  BinTreeNode* left_;
  BinTreeNode* right_;
};

// IsBinarySearchTree
bool is_bst(const BinTreeNode* n, const BinTreeNode* min,
            const BinTreeNode* max) {
  if (n == nullptr) {
    return true;
  }
  if (min && n->value_ < min->value_) {
    return false; // outside valid range
  }
  if (max && n->value_ > max->value_) {
    return false; // outside valid range
  }
  // Left side must be in range [min.value, n.value]
  // because when we go left the minimal value doesn't change, but 
  // the maximal is caped by the current node's value.
  // The same for the right side.
  return is_bst(n->left_, min, n) && is_bst(n->right_, n, max);
}

struct BinarySearchTree {
  BinarySearchTree() : root_{nullptr} {}

  BinTreeNode* Add(int value) {
    BinTreeNode** n = &root_;
    while (*n != nullptr) {
      n = value < (*n)->value_ ? &((*n)->left_) : &((*n)->right_);
    }
    *n = new BinTreeNode(value);
    return *n;
  }

  bool IsBinarySearchTree() const { return is_bst(root_, nullptr, nullptr); }

  BinTreeNode* root_;
};

int main() {
  BinarySearchTree b0;
  assert(b0.IsBinarySearchTree());

  BinarySearchTree b1;
  b1.Add(20);
  assert(b1.IsBinarySearchTree());
  b1.Add(10);
  assert(b1.IsBinarySearchTree());
  b1.Add(30);
  assert(b1.IsBinarySearchTree());
  auto p = b1.Add(15);
  assert(b1.IsBinarySearchTree());

  p->value_ = 25;
  assert(!b1.IsBinarySearchTree());

  std::cout << "OK" << std::endl;
}

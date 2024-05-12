/*
4.4
Check Balanced: Implement a function to check if a binary tree is balanced.
For the purposes of this question, a balanced tree is defined to be a tree
such that the heights of the two subtrees of any node never differ by more
than one.
Hints:#21, #33, #49, #105, #124
*/

#include <cassert>
#include <iostream>

struct BinTreeNode {
  BinTreeNode(int value) : value_{value}, left_{nullptr}, right_{nullptr} {}

  int value_;
  BinTreeNode* left_;
  BinTreeNode* right_;
};

// returns {depth, is_balanced}
std::pair<int, bool> check_height(const BinTreeNode* n) {
  if (n == nullptr) {
    return std::pair{-1, true}; // base case
  }
  const auto [depth1, is_balanced1] = check_height(n->left_);
  if (is_balanced1 == false) {
    return std::pair{-1, false};
  }
  const auto [depth2, is_balanced2] = check_height(n->right_);
  if (is_balanced2 == false) {
    return std::pair{-1, false};
  }
  bool is_balanced = std::abs(depth1 - depth2) <= 1;
  int max_depth = std::max(depth1, depth2) + 1;
  return std::pair{max_depth, is_balanced};
}

/*
Not efficient: O(N Log(N))

int get_height(const BinTreeNode* n) {
  if (n == nullptr) return - 1;
  return std::max(get_height(n->left_), get_height(n->right_)) + 1;
}

bool is_balanced(const BinTreeNode* n) {
  if (n == nullptr) return true;
  int diff = std::abs(get_height(n->left_) - get_height(n->right_));
  if (diff > 1) {
    return false;
  }
  return is_balanced(n->left_) && is_balanced(n->right_);
}
*/

struct BinarySearchTree {
  BinarySearchTree() : root_{nullptr} {}
  void Add(int value) {
    BinTreeNode** n = &root_;
    while (*n != nullptr) {
      n = value < (*n)->value_ ? &((*n)->left_) : &((*n)->right_);
    }
    *n = new BinTreeNode(value);
  }

  bool IsBalanced() const {
    return check_height(root_).second;
  }

  BinTreeNode* root_;
};

int main() {
  BinarySearchTree b0;
  assert(b0.IsBalanced());

  BinarySearchTree b1;
  b1.Add(10);
  assert(b1.IsBalanced());
  b1.Add(5);
  assert(b1.IsBalanced());
  b1.Add(15);
  assert(b1.IsBalanced());
  b1.Add(2);
  assert(b1.IsBalanced());
  b1.Add(1);
  assert(!b1.IsBalanced());
  b1.Add(6);
  assert(!b1.IsBalanced());
  b1.Add(12);
  assert(b1.IsBalanced());
  b1.Add(11);
  assert(!b1.IsBalanced());

  BinarySearchTree b2;
  assert(b2.IsBalanced());
  b2.Add(3);
  assert(b2.IsBalanced());
  b2.Add(2);
  assert(b2.IsBalanced());
  b2.Add(1);
  assert(!b2.IsBalanced());

  std::cout << "OK" << std::endl; 
}

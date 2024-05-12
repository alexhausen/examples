/*
4.2
Minimal Tree:
Given a sorted (increasing order) array with unique integer elements,
write an algo­rithm to create a binary search tree with minimal height.
Hints: #19, #73, #116
*/

#include <cassert>
#include <iostream>
#include <vector>

struct Node {
  Node(int value): left_{nullptr}, right_{nullptr}, value_{value} {}

  Node* left_;
  Node* right_;
  int value_;
};

void tree_depth(Node* n, unsigned current, unsigned& max) {
  if (n == nullptr) return;
  current++;
  if (current > max) max = current;
  tree_depth(n->left_, current, max);
  tree_depth(n->right_, current, max);
}

Node* insert(const std::vector<int>& v, int l, int r) {
  if (l > r) return nullptr;
  int i = l + ((r - l) / 2);
  Node* n = new Node(v[i]);
  n->left_ = insert(v, l, i - 1);
  n->right_ = insert(v, i + 1, r);
  return n;
}

class MinTree {
 public:

  MinTree(const std::vector<int>& v): root_{nullptr} {
    int l = 0;
    int r = v.size() - 1;
    root_ = insert(v, l, r);
  }

  unsigned depth() const {
    unsigned d = 0;
    tree_depth(root_, 0, d);
    return d;
  }

 private:
  Node* root_;
};

int main() {

  auto t0 = MinTree({});
  assert(0 == t0.depth());
  auto t1 = MinTree({1});
  assert(1 == t1.depth());
  auto t2 = MinTree({1, 2, 3});
  assert(2 == t2.depth());
  auto t3 = MinTree({1, 2, 3, 4});
  assert(3 == t3.depth());
  auto t4 = MinTree({1, 2, 3, 4, 5, 6, 7});
  assert(3 == t4.depth());

  std::cout << "OK" << std::endl;
}

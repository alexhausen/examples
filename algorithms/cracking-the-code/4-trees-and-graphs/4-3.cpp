/*
4.3
List of Depths: Given a binary tree, design an algorithm which creates a 
linked list of all the nodes at each depth (e.g., if you have a tree with
depth D, you'll have D linked lists).
Hints: #107, #123, #135
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <functional>

struct Node {
  Node(int value): value_{value}, left_{nullptr}, right_{nullptr} {}

  int value_;
  Node* left_;
  Node* right_;
};

struct BinarySearchTree {
  BinarySearchTree():root_{nullptr}{}

  void add(int value) {
    Node** n = &root_;
    while (*n != nullptr) {
      n = (value <= (*n)->value_) ? &((*n)->left_) : &((*n)->right_);
    }
    *n = new Node(value);
  }

  Node* root_;
};

void dfs(const Node* n, unsigned level, std::function<void(int,int)> fn) {
  if (n == nullptr) {
    return;
  }
  fn(level, n->value_);
  dfs(n->left_, level + 1, fn);
  dfs(n->right_, level + 1, fn);
}

/*
It's also possible to implement it with a bfs algorithm

bfs(Node* n) {
  if (root == nullptr) {
    return;
  }
  current.push_back(root_);
  while (!current.empty()) {
    results.push_back(current);
    parents = current;
    current = {};
    for (auto& parent: parents) {
      if (parent->left_ != nullptr) {
        current.push_back(parent->left_);
      }
      if (parent->right_ != nullptr) {
        current.push_back(parent->right_);
      }
    }
  }
}
*/

std::vector<std::vector<int>> bin_tree_to_lists(const BinarySearchTree& bt) {
  std::vector<std::vector<int>> v;
  unsigned level = 0;
  dfs(bt.root_, level, [&](unsigned lvl, int value) {
    if (lvl + 1 > v.size()) {
      v.push_back({});
    }
    v[lvl].push_back(value);
    // std::cout << lvl << ": " << value << std::endl;
  });
  return v;
}

int main() {

  BinarySearchTree t0;
  std::vector<std::vector<int>> r0 = bin_tree_to_lists(t0);
  std::vector<std::vector<int>> expected0{};
  assert(r0 == expected0);

  BinarySearchTree t1;
  t1.add(2);
  t1.add(1);
  t1.add(4);
  t1.add(3);
  t1.add(5);
  std::vector<std::vector<int>> r1 = bin_tree_to_lists(t1);
  std::vector<std::vector<int>> expected1{{2}, {1, 4}, {3, 5}};
  assert(r1 == expected1);

  BinarySearchTree t2;
  t2.add(1);
  t2.add(2);
  t2.add(3);
  t2.add(4);
  t2.add(5);
  std::vector<std::vector<int>> r2 = bin_tree_to_lists(t2);
  std::vector<std::vector<int>> expected2{{1}, {2}, {3}, {4}, {5}};
  assert(r2 == expected2);

  std::cout << "OK" << std::endl;
}

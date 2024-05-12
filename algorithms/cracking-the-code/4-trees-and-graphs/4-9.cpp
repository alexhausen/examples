/*
4.9
BST Sequences: A binary search tree was created by traversing through an array 
from left to right and inserting each element. Given a binary search tree with 
distinct elements, print all possible arrays that could have led to this tree.
Hints: #39, #48, #66, #82
*/

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
  Node(int value):value_{value}, left_{nullptr}, right_{nullptr} {}

  int value_;
  Node* left_;
  Node* right_;
};

/*
void df(Node* n, vector<vector<int>>& levels, int level) {
  if (n == nullptr) return;
  df(n->left_, levels, level + 1);
  df(n->right_, levels, level + 1);

  if (level + 1 > levels.size()) {
    levels.push_back({});
  }
  levels[level].push_back(n->value_);
}
*/

struct BinSearchTree {
  BinSearchTree(): root_{nullptr} {}

  void AddNode(int value) {
    Node** pp = &root_;
    while (*pp != nullptr) {
      if (value < (*pp)->value_) {
        pp = &(*pp)->left_;
      } else {
        pp = &(*pp)->right_;
      }
    }
    *pp = new Node(value);
  }


  void PrintAllSeq() const {
/*
    vector<vector<int>> levels;
    df(root_, levels, 0);
*/
    // TODO
    cout << endl;
  }

  Node* root_;
};

int main() {
  BinSearchTree b0;
  b0.PrintAllSeq();

  BinSearchTree b1;
  b1.AddNode(1);
  b1.PrintAllSeq();

  BinSearchTree b2;
  b2.AddNode(2);
  b2.AddNode(1);
  b2.AddNode(3);

  BinSearchTree b3;
  b3.AddNode(5);
  b3.AddNode(2);
  b3.AddNode(7);
  b3.AddNode(1);
  b3.AddNode(3);
  b3.AddNode(9);
  b3.AddNode(10);
}

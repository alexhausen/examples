/*
4.1O
Check Subtree: Tl and T2 are two very large binary trees, with Tl much bigger 
than T2. Create an algorithm to determine if T2 is a subtree of Tl.
A tree T2 is a subtree of Tl if there exists a node n in Tl such that the 
subtree of n is identical to T2.
That is, if you cut off the tree at node n, the two trees would be identical.
Hints: #4, #11, #18, #31, #37
*/

#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node {
  Node(int value): value_{value}, left_{nullptr}, right_{nullptr} {}

  int value_;
  Node* left_;
  Node* right_;
};

struct BinTree {
  BinTree(): root_{nullptr}{}

  bool contains_1(const BinTree& t) const;

  bool contains_2(const BinTree& t) const;

  Node* root_;
};

Node* add_node(Node** n, int value) {
  *n = new Node(value);
  return *n;
}

// alternative 1:

void pre_order_str(const Node* t, stringstream& ss) {
  if (t == nullptr) {
    // add a placeholder to identify null and so we can check the structure 
    // of the subtree
    ss << "x"; 
    return;
  }
  ss << t->value_ << " ";
  pre_order_str(t->left_, ss);
  pre_order_str(t->right_, ss);
}

// check if t1 contains the subtree t2
//   - generate a pre-order string 's' of each trees
//   - s of t2 should be a substring of s of t1
//   - consider the tree structure by using placeholders for null nodes
// Time: O(n+m)
// Space: O(n+m)
bool contains_1(const Node* t1, const Node* t2) {
  stringstream s1;
  pre_order_str(t1, s1);
  stringstream s2;
  pre_order_str(t2, s2);
  return s1.str().find(s2.str()) != string::npos;
}

// alternative 2:
bool match(const Node* t1, const Node* t2) {
  if (t1 == nullptr && t2 == nullptr) {
    return true; // both subtrees matched
  }
  if (t1 == nullptr || t2 == nullptr) {
    return false;
  }
  if (t1->value_ != t2->value_) {
    return false;
  }
  return match(t1->left_, t2->left_) && match (t1->right_, t2->right_);
}

// check if t1 contains the subtree t2
//
// Time: O(nm) worst case; O(n + km) / k = number of times t2's root appears in t1
// Space: O(log(n) + log(m)), on a balanced tree
bool contains_2(const Node* t1, const Node* t2) {
  if (t1 == nullptr) {
    return false;
  } else if (t1->value_ == t2->value_ && match(t1, t2)) {
    return true;
  }
  return contains_2(t1->left_, t2) || contains_2(t1->right_, t2);
}

bool BinTree::contains_1(const BinTree& t) const {
  return ::contains_1(root_, t.root_);
}

bool BinTree::contains_2(const BinTree& t) const {
  if (t.root_ == nullptr) return true;
  return ::contains_2(root_, t.root_);
}


int main() {
  // t1 contains t2?
  BinTree t1;
  auto t1n1 = add_node(&t1.root_, 1);
  auto t1n2 = add_node(&t1n1->left_, 2);
  [[maybe_unused]]
  auto t1n3 = add_node(&t1n1->right_, 3);
  [[maybe_unused]]
  auto t1n4 = add_node(&t1n2->left_, 4);

  BinTree t2;
  auto t2n2 = add_node(&t2.root_, 2);
  [[maybe_unused]]
  auto t2n4 = add_node(&t2n2->left_, 4);;

  assert(t1.contains_1(t2));
  assert(t1.contains_2(t2));

  assert(!t2.contains_1(t1));
  assert(!t2.contains_1(t1));

  // tx contains ty?
  BinTree tx;
  BinTree ty;

  assert(tx.contains_1(ty));
  assert(tx.contains_2(ty));

  add_node(&tx.root_, 3);
  add_node(&ty.root_, 3);

  assert(tx.contains_1(ty));
  assert(tx.contains_2(ty));

  add_node(&tx.root_->left_, 4);
  add_node(&ty.root_->right_, 4);

  assert(!tx.contains_1(ty));
  assert(!tx.contains_2(ty));

  assert(tx.contains_1(tx));
  assert(tx.contains_2(tx));

  cout << "OK" << endl;
}

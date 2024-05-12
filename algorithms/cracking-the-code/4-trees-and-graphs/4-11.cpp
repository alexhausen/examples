/*
4.11
Random Node: You are implementing a binary search tree class from scratch,
which, in addition to insert, find, and delete, has a method getRandomNode()
which returns a random node from the tree. All nodes should be equally likely
to be chosen. Design and implement an algorithm for getRandomNode, and explain
how you would implement the rest of the methods.
Hints: #42, #54, #62, #75, #89, #99, #112, #119
*/

#include <cassert>
#include <iostream>

// random number in range [0, limit[
int random_number(int limit) {
  // TODO
  return 42 % limit;
}

struct BinarySearchTreeNode {

  int value_;
  BinarySearchTreeNode* left_;
  BinarySearchTreeNode* right_;
  int size_;  // subtree size

  BinarySearchTreeNode(int value)
      : value_{value}, left_{nullptr}, right_{nullptr}, size_{1} {}

  void Insert(int value) {
    // increase size in each node travesed
  }

  void Delete(int value) {
    // decrease size in each node travesed
  }

  const BinarySearchTreeNode* Find() const {
    // no change
    return nullptr;
  }

  // On each node get a random (1/N) chance on the subtree
  // Time O(depth); O(log N) for a balanced tree
  // Space O(N)
  const BinarySearchTreeNode* GetRandomNode() const {
    int left_size = left_ ? left_->size_ : 0;
    int r = random_number(left_size);
    if (r < left_size) {
      return left_->GetRandomNode();
    } else if (r > left_size) {
      return right_->GetRandomNode();
    }
    return this;
  }
};

int main() {
  // TODO
  std::cout << "OK" << std::endl;
}

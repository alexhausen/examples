/*
4.12
Paths with Sum: You are given a binary tree in which each node contains an
integer value (which might be positive or negative). Design an algorithm to
count the number of paths that sum to a given value. The path does not need
to start or end at the root or a leaf, but it must go downwards (traveling
only from parent nodes to child nodes).
Hints: #6, #14, #52, #68, #77, #87, #94, #103, #108, #115
*/

#include <cassert>
#include <iostream>
#include <unordered_map>

using namespace std;

struct BinTreeNode;
bool HasPathSum(const BinTreeNode* n, int expected_value, int acc);

struct BinTreeNode {
  BinTreeNode(int value) : value_{value}, left_{nullptr}, right_{nullptr} {}

  void Insert(int value) {
    // TODO
  }

  int PathsWithSum(int target_sum) const {
    unordered_map<int, int> hash;
    return CountPathsWithSum(this, target_sum, 0, hash);
  }

  // Time Complexity: O(N)  
  static int CountPathsWithSum(const BinTreeNode* n, int target_sum,
                               int current_sum, unordered_map<int, int>& hash) {
    if (n == nullptr) {
      return 0;
    }
    current_sum += n->value_;
    // find a point in the nodes from the path above
    // which the difference current will get to the target
    int sum = current_sum - target_sum;
    auto it = hash.find(sum);
    int total_paths = (it != hash.end()) ? it->second : 0;
    if (current_sum == target_sum) {
      // here we have a path from root to the current node that get to the
      // target
      total_paths++;
    }
    if (hash.count(current_sum) == 0) {
      hash[current_sum] = 0;
    }
    hash[current_sum]++;
    total_paths +=
        CountPathsWithSum(n->left_, target_sum, current_sum + n->value_, hash);
    total_paths +=
        CountPathsWithSum(n->right_, target_sum, current_sum + n->value_, hash);
    // remove the current sum so we don't count it on paths that don't include
    // this node
    hash[current_sum]--;
    return total_paths;
  }

  /*
  // Time: O(N logN); for every node search depth
  int PathsWithSum(int expected_value) const {
    int paths = 0;
    PathsWithSumImpl(expected_value, paths);
    return paths;
  }

  void PathsWithSumImpl(int expected_value, int& paths) const {
    if (HasPathSum(this, expected_value, 0)) {
      paths++;
    }
    if (left_) {
      left_->PathsWithSumImpl(expected_value, paths);
    }
    if (right_) {
      right_->PathsWithSumImpl(expected_value, paths);
    }
  }

  static bool HasPathSum(const BinTreeNode* n, int target_sum, int current_sum)
  { if (current_sum == target_sum) { return true;
    }
    if (n == nullptr) {
      return false;
    }
    return HasPathSum(n->left_, target_sum, current_sum + n->value_) ||
          HasPathSum(n->right_, target_sum, current_sum + n->value_);
  }
  */

  int value_;
  BinTreeNode* left_;
  BinTreeNode* right_;
};

/*
 */

int main() {
  // TODO
  std::cout << "OK" << std::endl;
}

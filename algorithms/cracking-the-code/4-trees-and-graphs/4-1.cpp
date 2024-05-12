/*
4.1
Route Between Nodes: Given a directed graph, design an algorithm to find out
whether there is a route between two nodes. Hints:#127
*/

#include <cassert>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>

class graph {
 public:
  void add_node(char n, const std::vector<char>& e) {
    nodes_[n].insert(e.begin(), e.end());
  }

  void print() const {
    for (const auto& [n, es] : nodes_) {
      std::cout << n << " : { ";
      for (const auto& e : es) {
        std::cout << e << " ";
      }
      std::cout << "}" << std::endl;
    }
  }

  // Using BFS (breath-first search).
  // It's better than DFS (depth-first search) because we search
  // the number of levels from src to dst.
  bool has_path(char src, char dst) const {
    std::queue<char> q;
    auto it = nodes_.find(src);
    assert(it != nodes_.end());
    const auto& children = (*it).second;
    for (const auto& child : children) {
      q.push(child);
    }
    std::vector<char> visited;
    visited.insert(src);
    while (!q.empty()) {
      auto n = q.front();
      if (n == dst) {
        return true;
      }
      q.pop();
      if (visited.contains(n)) {
        continue;
      }
      visited.insert(n);
      it = nodes_.find(n);
      assert(it != nodes_.end());
      const auto& children = (*it).second;
      for (const auto& child: children) {
        q.push(child);
      }
    }
    return false;
  }

 private:
  std::unordered_map<char, std::vector<char>> nodes_;
};

int main() {
  graph g;
  g.add_node('a', {'b', 'c', 'g'});
  g.add_node('b', {'d'});
  g.add_node('c', {'e'});
  g.add_node('d', {'f', 'c'});
  g.add_node('e', {'d'});
  g.add_node('f', {});
  g.add_node('g', {});
  // g.print();

  assert(g.has_path('a', 'd'));
  assert(g.has_path('b', 'c'));
  assert(!g.has_path('b', 'g'));

  std::cout << "OK" << std::endl;
}

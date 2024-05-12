/*
8.2
Robot in a Grid: Imagine a robot sitting on the upper left corner of grid with
r rows and c columns. The robot can only move in two directions, right and down,
but certain cells are "off limits" such that the robot cannot step on them.
Design an algorithm to find a path for the robot from the top left to the bottom
right.
Hints: #331, #360, #388
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

using Grid = vector<vector<char>>;
using Path = vector<pair<int, int>>;

bool off_limits(const Grid& grid, int r, int c) {
  return r < 0 || c < 0 || grid[r][c] == 'x';
}

// Time complexity: O(2^n)
bool walk_1(const Grid& grid, int r, int c, Path& path) {
  if (off_limits(grid, r, c)) {
    return false;
  }
  bool finished = r == 0 && c == 0;
  if (finished || 
      walk_1(grid, r - 1, c, path) ||
      walk_1(grid, r, c - 1, path)) {
    path.push_back(pair(r, c));
    return true;
  }
  return false;
}

Path get_robot_path_1(const Grid& g) {
  Path path;
  walk_1(g, g.size() - 1, g[0].size() - 1, path);
  return path;
}

// Optimized to use a hash set for the cells that fail to be in the path
// Time complexity: O(N*M)
auto hash_t = [](const pair<int, int>& p) { return p.first * 31 + p.second; };
using Hash = unordered_set<pair<int, int>, decltype(hash_t)>;

bool walk_2(const Grid& grid, int r, int c, Path& path, Hash& fails) {
  if (off_limits(grid, r, c)) {
    return false;
  }
  pair<int, int> cell = pair(r, c);
  if (fails.contains(cell)) {
    return false;
  }
  bool finished = r == 0 && c == 0;
  if (finished || 
      walk_2(grid, r - 1, c, path, fails) ||
      walk_2(grid, r, c - 1, path, fails)) {
    path.push_back(cell);
    return true;
  }
  fails.insert(cell);
  return false;
}

Path get_robot_path_2(const Grid& g) {
  Path path;
  Hash fails;
  walk_2(g, g.size() - 1, g[0].size() - 1, path, fails);
  return path;
}

void print_path(const Path& path) {
  for (const auto& [a,b] : path) {
    cout << "(" << a << "," << b << ")";
  }
  cout << endl;
}

int main() {
  const Grid g1 = { //
      {' ', ' '}, // 
      {'x', ' '}, // 
  };
  const Grid g2 = { //
      {' ', ' ', ' ', ' ', ' '}, // 
      {' ', ' ', ' ', ' ', ' '}, // 
      {' ', ' ', ' ', ' ', ' '}, //
      {' ', ' ', ' ', ' ', ' '}, //
      {' ', ' ', ' ', ' ', ' '}, //
  };

  Path path1a = get_robot_path_1(g1);
  print_path(path1a);

  Path path2a = get_robot_path_1(g2);
  print_path(path2a);

  Path path1b = get_robot_path_2(g1);
  print_path(path1b);

  Path path2b = get_robot_path_2(g2);
  print_path(path2b);

  cout << "OK" << endl;
}

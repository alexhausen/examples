/*
4.7
Build Order: You are given a list of projects and a list of dependencies
(which is a list of pairs of projects, where the second project is dependent 
on the first project). All of a project's dependencies must be built before 
the project is. Find a build order that will allow the projects to be built. 
If there is no valid build order, return an error.
EXAMPLE
Input:
projects: a, b, c, d, e, f
dependencies: (a, d), (f, b), (b, d), (f, a), (d, c)
Output: f, e, a, b, d, c
Hints: #26, #47, #60, #85, #125, #133
*/

#include <cassert>
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void build_order(vector<char> prjs, const vector<pair<char, char>>& deps) {
  unordered_map<char, vector<char>> g;
  for (auto p : prjs) {
    g[p] = {};
  }
  for (auto [a, b]: deps) {
    g[b].push_back(a);
  }
  // TODO!
}

int main() {

  vector<char> projects {'a', 'b', 'c', 'd', 'e', 'f'};
  vector<pair<char, char>> dependencies {
    {'a', 'd'},
    {'f', 'b'},
    {'b', 'd'},
    {'f', 'a'},
    {'d', 'c'}
  };

  build_order(projects, dependencies);

  cout << "TODO!" << endl;
}

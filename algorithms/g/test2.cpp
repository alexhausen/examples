
//std::optional<unsigned>

#include <set>
#include <vector>

using namespace std;

struct Interval {
  unsigned min;
  unsigned max;
};

vector<Interval> make_interval(vector<unsigned>& minSdk, vector<unsigned>& maxSdk) {
  vector<Interval> intervals;
  vector<unsigned> s;
  for (auto min: minSdk) {
    if (min != 0)
      s.insert(min);
  }
  for (auto max: maxSdk) {
    if (max != 0)
      s.insert(max);
  }
  if (s.empty()) return intervals;
  
  // set { 3, 4, 7, 10, 16}
  
  intervals.push_back(Interval(0, *s.begin()-1));
  // {0, 2}
 
  for (auto it = s.begin(); it != s.end(); ++it) {
    // first = *it;
    // second = *(it + 1) - 1;
    Interval v;
    v.min = first;
    v.max = second;
    intervals.push_back(v);
    // {3, 3}
    // + {4, 6}
    // + {7, 9} // wrong
  }
  intervals.push_back(Interval(*s.back()+1, 0));
  return intervals;
}


int main() {
  // assert(extected == make_interval(v1, v2));
}

/*
  A: 3 -
  B: 7 10
  C: 4 16

  A: 3 5
  B: 6 10

  (<=2), (3, 5), (6, 10) (>= 11)
*/
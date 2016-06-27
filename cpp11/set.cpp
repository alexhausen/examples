#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cassert>

template <class T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
  os << "{ ";
  for (const auto& k : s) {
    os << k << " ";
  }
  os << "}";
  return os;
}

template <class T>
std::set<T> operator - (const std::set<T>& s1, const std::set<T>& s2) {
  std::set<T> diff;
  std::set_difference(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(diff, diff.begin()));
  return diff;
}

template <class T>
std::set<T> operator % (const std::set<T>& s1, const std::set<T>& s2) {
  std::set<T> intersection;
  std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), std::inserter(intersection, intersection.begin()));
  return intersection;
}

template <class T>
bool operator == (const std::set<T>& s1, const std::set<T>& s2) {
  if (s1.size() != s2.size()) return false;
  typename std::set<T>::const_iterator it1 = s1.begin();
  typename std::set<T>::const_iterator it2 = s2.begin();
  while (it1 != s1.end() && it2 != s2.end()) {
    if (*it1 != *it2) return false;
    ++it1;
    ++it2;
  }
  return true;
}

int main() {
  std::set<char> A = { 'a', 'b' };
  std::set<char> B = { 'b', 'c' };

  std::cout << "A = " << A << std::endl;
  assert(A == A);  
  std::cout << "B = " << A << std::endl;
  assert(B == B);
  std::cout << "A - B  = " << (A - B) << std::endl;
  assert(A - B == std::set<char>{ 'a' });
  std::cout << "B - A = " << (B - A) << std::endl;
  assert(B - A == std::set<char>{ 'c' });
  std::cout << "A % B = " << (A % B) << std::endl;
  assert(A % B == std::set<char>{'b'});
}

#include <vector>
#include <iostream>
#include <algorithm>
 
int main()
{
    std::vector<int> v{2, 4, 2, 0, 5, 10, 7, 3, 7, 1}; 
 
    std::cout << "before sort: { ";
    for (int n : v)
        std::cout << n << ' ';
    std::cout << "}\n\n";
 
    // insertion sort
    std::cout << "sorting:\n";
    for (auto i = v.begin(); i != v.end(); ++i) {
        auto upper_bound = std::upper_bound(v.begin(), i, *i);
        std::cout << "rotating: { ";
        for (auto j = v.begin(); j!=i+1;++j)
          std::cout << *j << ' ';
        std::cout << "} first(upper) = " << *upper_bound << ", n_first(new) = " << *i << "\n";
        std::rotate(upper_bound, i, i+1);
        std::cout << "rotated:  { ";
        for (auto j = v.begin(); j!=i+1;++j)
          std::cout << *j << ' ';
        std::cout << "}\n\n";
    }
 
    std::cout << "after sort: ";
    for (int n : v)
        std::cout << n << ' ';
    std::cout << "}\n";
 /*
    // simple rotation to the left
    std::rotate(v.begin(), v.begin() + 1, v.end());
 
    std::cout << "simple rotate left  : ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 
    // simple rotation to the right
    std::rotate(v.rbegin(), v.rbegin() + 1, v.rend());
    std::cout << "simple rotate right : ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
 */
}

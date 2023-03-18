// https://www.hackerrank.com/challenges/cpp-variadics/problem?isFullScreen=true

#include <iostream>
using namespace std;

// Enter your code for reversed_binary_value<bool...>()

template<bool digit>
int reversed_binary_value() {
    return static_cast<int>(digit);
}

template<bool d1, bool d2, bool ...digits>
int reversed_binary_value() {
    return static_cast<int>(d1) +
    2 * reversed_binary_value<d2, digits...>();
}

// end code


template <int n, bool...digits>
struct CheckValues {
    static void check(int x, int y)
    {
      CheckValues<n-1, 0, digits...>::check(x, y);
      CheckValues<n-1, 1, digits...>::check(x, y);
    }
};

template <bool...digits>
struct CheckValues<0, digits...> {
    static void check(int x, int y)
    {
      int z = reversed_binary_value<digits...>();
      std::cout << (z+64*y==x);
    }
};

int main()
{
    int t; std::cin >> t;

    for (int i=0; i!=t; ++i) {
    int x, y;
      cin >> x >> y;
      CheckValues<6>::check(x, y);
      cout << "\n";
    }
}

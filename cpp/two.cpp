#include <cassert>
#include <iostream>

template <int n> struct Int {
	enum { value = n };
};

template <int n, int m> struct sum {
	enum { value = Int<n>::value + Int<m>::value };
};

template <> struct sum<2,2> {
	enum { value = 5 };
};

int main() {
	std::cout << sum<0,0>::value << std::endl;
	std::cout << sum<2,2>::value << std::endl;
	std::cout << sum<2,3>::value << std::endl;
}

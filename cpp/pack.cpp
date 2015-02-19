#include <vector>
#include <iostream>
#include <cstdint>
#include <cassert>
#include <cstring>

struct X {
	int a;
	int b;
	int c;
};

std::vector<uint8_t> pack(const X& x) {
	std::vector<uint8_t> v;
	v.resize(3 * sizeof(int));
	std::memcpy(&v[0], &x.a, sizeof(int));
	std::memcpy(&v[4], &x.b, sizeof(int));
	std::memcpy(&v[8], &x.c, sizeof(int));
	return v;
}

int main() {
	X x = { 1, 2, 3 };
	std::vector<uint8_t> data = pack(x);

	std::vector<uint8_t> expected = { 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0 };

	assert(data.size() == expected.size());
	assert(data == expected);

	std::cout << "OK" << std::endl;

	return 0;
}

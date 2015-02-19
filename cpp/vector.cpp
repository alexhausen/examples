#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<uint8_t> v;
	v.resize(128);

	int x = 10;
	int y = 255;
	unsigned sz = 0;

	memcpy(&v[sz], &x, sizeof(int));
	//*(int*)&v[sz] = x;
	sz += sizeof(int);

	memcpy(&v[sz], &y, sizeof(int));
	sz += sizeof(int);

	v.resize(sz);
	cout << v.capacity() << endl;
	cout << v.size() << endl;

	for (uint8_t& c : v) {
		cout << static_cast<int>(c) << endl;
	}

	return 0;
}


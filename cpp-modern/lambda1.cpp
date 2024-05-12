#include <iostream>
#include <functional>

void foo(std::function<void(int)> f) {
	f(1);
}

int main() {

	int x = 10;

	auto lambda = [=] (int y) { std::cout << (x + y) << std::endl; };

	foo(lambda);

	return 0;
}


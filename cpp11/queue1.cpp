// g++ -std=c++0x -Wall -Wextra queue1.cpp

#include "queue1.h"

int main() {

	using x::Queue;

	Queue<int> q = {1, 2, 3};
	q.push(4);
	q.push(5);
	q.push(6);

	std::cout << "{ " ;
	while (!q.empty()) {
		std::cout << q.pop() << " ";
	}
	std::cout << "}" << std::endl;

	return 0;
}


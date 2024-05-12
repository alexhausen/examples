// g++ -std=c++0x -Wall -Wextra main_event_queue.cpp event_queue.cpp semaphore.cpp -pthread

#include <iostream>

#include "event_queue.h"

int main() {

	std::cout  << __PRETTY_FUNCTION__ << " main thread: " << std::this_thread::get_id() << std::endl;

	x::EventQueue eq;

	eq.post([]{ std::cout << "1" << std::endl; });
	eq.post([]{ std::cout << "2" << std::endl; });
	eq.post([]{ std::cout << "3" << std::endl; });

	return 0;
}


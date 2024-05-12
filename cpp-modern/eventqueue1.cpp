#include <atomic>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include "semaphore.h"

namespace x {

class EventQueue {
public:
	typedef std::function<void()> Closure;

	EventQueue() : running_(true), t_(&EventQueue::run, this) {
	}

	~EventQueue() {
		post([&]{ this->running_.store(false); });
		t_.join();
	}

	void post(Closure closure) {
		{
			std::lock_guard<std::mutex> lock(mtx_);
			q_.push(closure);
		}
		s_.post();
	}

private:

	void run() {
		std::cout << __PRETTY_FUNCTION__ << " worker thread: " << std::this_thread::get_id() << std::endl;
		do {
			mtx_.lock();
			if (!q_.empty()) {
				auto f = q_.front();
				q_.pop();
				mtx_.unlock();
				f();
			}
			mtx_.unlock();
			s_.wait();
		} while (running_.load());
	}

	std::queue<Closure> q_;
	Semaphore s_;
	std::mutex mtx_;
	std::atomic_bool running_;
	std::thread t_;
};

}

int main() {

	std::cout  << __PRETTY_FUNCTION__ << " main thread: " << std::this_thread::get_id() << std::endl;

	x::EventQueue eq;
	eq.post([]{ std::cout << "1" << std::endl; });
	eq.post([]{ std::cout << "2" << std::endl; });
	eq.post([]{ std::cout << "3" << std::endl; });

	return 0;
}


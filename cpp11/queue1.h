#pragma once

#include <initializer_list>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdexcept>

namespace x {

//thread safe queue
template <typename T> class Queue {
public:
	Queue() : q_{} { }

	Queue(const std::initializer_list<T>& l) : q_{l} { }

	Queue(const Queue&) = delete;

	Queue& operator=(const Queue&) = delete;

	void push(const T& v) {
		std::lock_guard<std::mutex> lock(mtx_);
		q_.push(v);
	}

	T&& pop() {
		std::lock_guard<std::mutex> lock(mtx_);
		if (q_.empty()) {
			throw std::runtime_error("Pop from empty Queue.");
		}
		T x = q_.front();
		q_.pop();
		return std::move(x);
	}

	bool empty() const noexcept {
		std::lock_guard<std::mutex> lock(mtx_);
		return q_.empty();
	}

	size_t size() const noexcept {
		std::lock_guard<std::mutex> lock(mtx_);
		return q_.size();
	}

private:
	std::queue<T> q_;
	mutable std::mutex mtx_;
};

} // namespace x


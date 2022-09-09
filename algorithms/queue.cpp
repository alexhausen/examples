// queue (FIFO first-in first-out)

#include <cassert>

#include <iostream>
#include <stdexcept>

template <class T>
class queue final {
   public:
    queue(unsigned reserve) : size_{0}, capacity_{0}, q_{nullptr} {
        q_ = reserve ? new T[reserve] : nullptr;
        capacity_ = reserve;
    }

    queue() : queue(default_capacity) {}

    ~queue() noexcept { delete[] q_; }

    auto empty() const noexcept -> bool { return size_ == 0; }

    auto size() const noexcept -> unsigned { return size_; }

    auto capacity() const noexcept -> unsigned { return capacity_; }

    auto push(const T& value) -> void {
        if (size_ == capacity_) {
            unsigned new_capacity =
                static_cast<unsigned>(static_cast<float>(capacity_) * resize_factor);
            capacity_ = std::max(new_capacity, default_capacity);
            auto temp = new T[capacity_];
            for (unsigned i = 0; i < size_; i++)
                temp[i] = q_[i];
            delete[] q_;
            q_ = temp;
        }
        q_[size_] = value;
        size_++;
    }

    auto pop() -> T {
        if (size_ == 0)
            throw std::exception();
        T front = q_[0];
        for (unsigned i = 1; i < size_; i++)
            q_[i - 1] = q_[i];
        size_--;
        return front;
    }

    auto shrink() -> void {
        if (capacity_ > size_) {
            auto temp = size_ ? new T[size_] : nullptr;
            for (unsigned i = 0; i < size_; i++)
                temp[i] = q_[i];
            delete[] q_;
            q_ = temp;
            capacity_ = size_;
        }
    }

   private:
    unsigned size_;
    unsigned capacity_;
    T* q_;

    static constexpr unsigned default_capacity = 5;
    static constexpr float resize_factor = 1.5f;
};

int main() {
    queue<int> q1;
    assert(q1.empty());
    assert(q1.capacity() == 5);
    q1.push(1);
    assert(!q1.empty());
    assert(q1.size() == 1);
    assert(q1.capacity() == 5);
    q1.push(2);
    q1.push(3);
    q1.push(4);
    q1.push(5);
    q1.push(6);
    assert(q1.size() == 6);
    assert(q1.capacity() == 7);
    assert(q1.pop() == 1);
    assert(q1.pop() == 2);
    assert(q1.pop() == 3);
    assert(q1.pop() == 4);
    assert(q1.pop() == 5);
    assert(q1.pop() == 6);
    assert(q1.empty());
    try {
        assert(q1.pop());
        assert(false);
    } catch (...) {
    }
    assert(q1.capacity() == 7);
    q1.shrink();
    assert(q1.capacity() == 0);
    assert(q1.empty());

    queue<int> q2(0);
    assert(q2.empty());
    assert(q2.capacity() == 0);
    q2.shrink();
    assert(q2.capacity() == 0);
    assert(q2.empty());
    q2.push(1);
    assert(q2.pop() == 1);
    assert(q2.empty());
    assert(q2.capacity() == 5);

    std::cout << "OK" << std::endl;
}

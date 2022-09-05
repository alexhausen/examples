// stack (FILO first-in last-out)

#include <cassert>

#include <iostream>
#include <stdexcept>

template <class T>
class stack {
   public:
    stack(unsigned reserve) : top_{0}, capacity_{0}, s_{nullptr} {
        s_ = reserve ? new T[reserve] : nullptr;
        capacity_ = reserve;
    }

    stack() : stack(default_capacity) {}

    ~stack() noexcept { delete[] s_; }

    auto empty() const noexcept -> bool { return top_ == 0; }

    auto size() const noexcept -> unsigned { return top_; }

    auto capacity() const noexcept -> unsigned { return capacity_; }

    auto push(const T& value) -> void {  //
        if (top_ == capacity_) {
            unsigned new_capacity =
                static_cast<unsigned>(static_cast<float>(capacity_) * resize_factor);
            capacity_ = std::max(new_capacity, default_capacity);
            auto temp = new T[capacity_];
            for (unsigned i = 0; i < top_; i++)
                temp[i] = s_[i];
            delete[] s_;
            s_ = temp;
        }
        s_[top_] = value;
        top_++;
    }

    auto pop() -> T {
        if (top_ == 0)
            throw std::exception();
        top_--;
        return s_[top_];
    }

    auto shrink() -> void {
        if (capacity_ > top_) {
            auto temp = top_ ? new T[top_] : nullptr;
            for (unsigned i = 0; i < top_; i++)
                temp[i] = s_[i];
            delete s_;
            s_ = temp;
            capacity_ = top_;
        }
    }

   private:
    unsigned top_;
    unsigned capacity_;
    T* s_;

    static constexpr unsigned default_capacity = 5u;
    static constexpr float resize_factor = 1.5f;
};

int main() {
    stack<int> s1;
    assert(s1.empty());
    assert(s1.capacity() == 5);
    s1.push(1);
    assert(!s1.empty());
    assert(s1.size() == 1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);
    assert(s1.capacity() == 5);
    s1.push(6);
    assert(s1.size() == 6);
    assert(s1.capacity() == 7);
    assert(s1.pop() == 6);
    assert(s1.pop() == 5);
    assert(s1.pop() == 4);
    assert(s1.pop() == 3);
    assert(s1.pop() == 2);
    assert(s1.pop() == 1);
    assert(s1.empty());
    try {
        s1.pop();
        assert(false);
    } catch (...) {
    }
    assert(s1.capacity() == 7);
    s1.shrink();
    assert(s1.capacity() == 0);

    stack<int> s2(0);
    assert(s2.empty());
    assert(s2.capacity() == 0);
    s2.shrink();
    assert(s2.capacity() == 0);
    assert(s2.empty());
    s2.push(1);
    assert(s2.pop() == 1);
    assert(s2.empty());
    assert(s2.capacity() == 5);

    std::cout << "OK" << std::endl;
}

// ring buffer (aka fixed size circular queue)

#include <cassert>

#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T, unsigned N>
// requires(N > 0)  // c++20 only
class ring_buffer {
   public:
    ring_buffer() : begin_{0}, size_{0} {}

    auto constexpr max_size() const noexcept -> unsigned { return N; }

    auto empty() const noexcept -> bool { return size_ == 0; }

    auto size() const noexcept -> unsigned { return size_; }

    auto push(const T& value) -> void {
        unsigned i = (begin_ + size_) % N;
        buf_[i] = value;
        if (size_ < N) {
            size_++;
        } else {
            begin_ = (begin_ + 1) % N;
        }
    }

    auto pop() -> T {
        if (empty())
            throw std::exception();
        T value = buf_[begin_];
        begin_ = (begin_ + 1) % N;
        size_--;
        return value;
    }

    auto front() const -> const T& {
        if (empty())
            throw std::exception();
        return buf_[begin_];
    }

    auto back() const -> const T& {
        if (empty())
            throw std::exception();
        unsigned i = (begin_ + size_ - 1) % N;
        return buf_[i];
    }

    auto to_vector() const -> std::vector<T> {
        std::vector<T> vec;
        vec.reserve(size_);
        for (unsigned i = 0; i < size_; i++) {
            vec.push_back(buf_[(begin_ + i) % N]);
        }
        return vec;
    }

    auto operator[](unsigned i) noexcept -> T& {
        // out-of-range is UB
        return buf_[(begin_ + i) % N];
    }

    auto at(unsigned i) -> T& {
        if (i >= size_)
            throw std::out_of_range("index out-of-range");
        return buf_[(begin_ + i) % N];
    }

   private:
    unsigned begin_ = 0;
    unsigned size_ = 0;
    T buf_[N];
};

int main() {
    // ring_buffer<int, 0> buf0;  // compile error in c++20 w/ requires(N>0)
    {
        ring_buffer<int, 5> buf;
        assert(buf.empty());
        assert(buf.size() == 0);
        assert(buf.max_size() == 5u);
        try {
            buf.pop();
            assert(false);
        } catch (const std::exception&) {
        }
        buf.push(1);
        assert(!buf.empty());
        assert(buf.size() == 1);
        assert(buf.front() == 1);
        assert(buf.back() == 1);
        std::vector<int> expected_vector1 = {1};
        assert(buf.to_vector() == expected_vector1);
        buf.push(2);
        buf.push(3);
        buf.push(4);
        assert(buf.front() == 1);
        assert(buf.back() == 4);
        buf.push(5);
        assert(buf.size() == 5);
        assert(buf.front() == 1);
        assert(buf.back() == 5);
        std::vector<int> expected_vector2 = {1, 2, 3, 4, 5};
        assert(buf.to_vector() == expected_vector2);
        buf.push(6);
        assert(buf.size() == 5);
        assert(buf.front() == 2);
        assert(buf.back() == 6);
        std::vector<int> expected_vector3 = {2, 3, 4, 5, 6};
        assert(buf.to_vector() == expected_vector3);
        assert(buf.pop() == 2);
        assert(buf.front() == 3);
        assert(buf.size() == 4);
        std::vector<int> expected_vector4 = {3, 4, 5, 6};
        assert(buf.to_vector() == expected_vector4);
        assert(buf[2] == 5);
        assert(buf.at(2) == 5);
        try {
            assert(buf.at(4));
            assert(false);
        } catch (const std::out_of_range&) {
        }
    }

    {
        ring_buffer<char, 1> buf;
        assert(buf.empty());
        assert(buf.size() == 0);
        assert(buf.max_size() == 1u);
        try {
            buf.front();
            assert(false);
        } catch (const std::exception&) {
        }
        buf.push('a');
        assert(buf.pop() == 'a');
        assert(buf.empty());
        buf.push('b');
        buf.push('c');
        assert(buf.size() == 1);
        assert(buf.front() == 'c');
        assert(buf.back() == 'c');
        assert(buf.pop() == 'c');
        assert(buf.empty());
    }

    {
        ring_buffer<char, 3> buf;
        buf.push('a');             // [a]
        buf.push('b');             // [a, b]
        buf.push('c');             // [a, b, c]
        buf.push('d');             //  d][b, c,
        buf.push('e');             //  d, e][c,
        buf.push('f');             // [d, e, f]
        buf.push('g');             //  g][e, f,
        assert(buf.pop() == 'e');  // g] - [f,
        assert(buf.size() == 2);
        std::vector<char> expected_char_vec = {'f', 'g'};
        assert(buf.to_vector() == expected_char_vec);
    }

    std::cout << "OK" << std::endl;
}

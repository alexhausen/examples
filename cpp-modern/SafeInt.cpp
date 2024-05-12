#include <iostream>
#include <cassert>
#include <stdexcept>
#include <limits>

// T must be signed integer (neither unsigned nor floating point);
// T must have arithmetic operations: +, -, /

template<class T>
class SafeInt {
public:
	SafeInt() : i_{0} {
		//TODO use concepts when available
		assert(std::numeric_limits<T>::is_signed);
		assert(!std::numeric_limits<T>::has_infinity);
	}

	SafeInt(const T x) : i_{x} {
		//TODO use concepts when available
		assert(std::numeric_limits<T>::is_signed);
		assert(!std::numeric_limits<T>::has_infinity);
	}

  SafeInt& operator=(const T x) {
		assert(std::numeric_limits<T>::is_signed);
		assert(!std::numeric_limits<T>::has_infinity);
    i_ = x;
    return *this;
  }

	operator T() const {
		return i_;
	}

  friend SafeInt operator+(const SafeInt& a, const SafeInt& b) {
    T r;
    if (__builtin_add_overflow(a.i_, b.i_, &r)) {
      throw std::runtime_error("overflow");
    }
    return SafeInt{r};
  }

  friend SafeInt operator+(T a, const SafeInt& b) {
    return SafeInt{a} + b;
  }

  friend SafeInt operator+(const SafeInt<T>& a, T b) {
    return a + SafeInt{b};
  }

  friend SafeInt operator-(const SafeInt& a, const SafeInt& b) {
    T r;
    if (__builtin_sub_overflow(a.i_, b.i_, &r)) {
      throw std::runtime_error("overflow");
    }
    return SafeInt{r};
  }

  friend SafeInt operator-(T a, const SafeInt& b) {
    return SafeInt{a} - b;
  }

  friend SafeInt operator-(const SafeInt& a, T b) {
    return a - SafeInt{b};
  }

  friend SafeInt operator*(const SafeInt& a, const SafeInt& b) {
    T r;
    if (__builtin_mul_overflow(a.i_, b.i_, &r)) {
      throw std::runtime_error("overflow");
    }
    return SafeInt{r};
  }

  friend SafeInt operator*(T a, const SafeInt& b) {
    return SafeInt{a} * b;
  }

  friend SafeInt operator*(const SafeInt& a, T b) {
    return a * SafeInt{b};
  }

	friend SafeInt operator/(const SafeInt& a, const SafeInt& b) {
		if (b.i_ == 0) {
			throw std::runtime_error("division by zero");
		}
		return SafeInt{a.i_ / b.i_};
	}

	friend SafeInt operator/(T a, const SafeInt& b) {
    return SafeInt{a} / b;
  }

	friend SafeInt operator/(const SafeInt& a, T b) {
    return a / SafeInt{b};
  }

  SafeInt abs() const {
    return i_ >= 0 ? *this : SafeInt{i_} * SafeInt{-1};
  }

/*
  // This is too slow. use compiler builtin instead.
	SafeInt operator+ (const SafeInt& other) const {
		// ((s1 > 0) & (s2 > 0) & (s1 > (int_max - s2))) | ((s1 < 0) & (s2 < 0) & (s1 < (int_min - s2)))
		const T int_min = std::numeric_limits<T>::min();
		const T int_max = std::numeric_limits<T>::max();
		const T s1 = i_;
		const T s2 = other.i_;
		bool overflow = ((s1 > 0) && (s2 > 0) && (s1 > (int_max - s2))) | ((s1 < 0) && (s2 < 0) && (s1 < (int_min - s2)));
		if (overflow) {
			throw std::runtime_error("overflow");
		}
		return SafeInt(i_ + other.i_);
	}
*/

private:
	T i_;
};

int main() {

	SafeInt<int> a = 1;
	SafeInt<int> b = 2;
	assert(3 == a + b);

	a = 0;
	b = 2;
	assert(0 == a/b);

	a = 1;
	b = 0;
	try {
		a / b;
		assert(false);
	} catch (const std::exception& e) {
		assert(std::string("division by zero") == e.what());
	}

  SafeInt<char> a1 = SafeInt<char>{100} + static_cast<char>(27);
  assert(a1 == 127);
  
  try {
    SafeInt<char>{100} + static_cast<char>(28);
    assert(false);
  } catch (const std::exception& e) {
		assert(std::string("overflow") == e.what());
	}

	SafeInt<char> c1 = 100;
	SafeInt<char> c2 = 27;
	assert(127 == c1 + c2);

	c1 = 100;
	c2 = 100;
	try {
		c1 + c2;
		assert(false);
	} catch (const std::exception& e) {
		assert(std::string("overflow") == e.what());
	}

  assert(SafeInt<char>{-127}.abs() == 127);

  try {
    SafeInt<char>{-128}.abs();
  } catch (const std::exception& e) {
    assert(std::string("overflow") == e.what());
  }

  try {
    SafeInt<int>{std::numeric_limits<int>::min()} - 1;
  } catch (const std::exception& e) {
    assert(std::string("overflow") == e.what());
  }

  try {
    SafeInt<char>{20} * static_cast<char>(20);
  } catch (const std::exception& e) {
    assert(std::string("overflow") == e.what());
  }

	// SafeInt<float> afloat; // run time failure
	// SafeInt<unsigned char> uchar; // run time failure

  std::cout << "ok" << std::endl;

  return 0;
}

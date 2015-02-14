#include <cassert>
#include <stdexcept>
#include <limits>

// T must be signed integer (neither unsigned nor floating point);
// T must have arithmetic operations: +, -, /
template<class T>
class SafeSignedInt {
public:
	SafeSignedInt() : internal_(0) {
		//TODO use concepts when available
		assert(std::numeric_limits<T>::is_signed);
		assert(!std::numeric_limits<T>::has_infinity);
	}

	SafeSignedInt(const T x) : internal_(x) {
		//TODO use concepts when available
		assert(std::numeric_limits<T>::is_signed);
		assert(!std::numeric_limits<T>::has_infinity);
	}

	SafeSignedInt operator+ (const SafeSignedInt& other) const {
		// ((s1 > 0) & (s2 > 0) & (s1 > (int_max - s2))) | ((s1 < 0) & (s2 < 0) & (s1 < (int_min - s2)))
		const T int_min = std::numeric_limits<T>::min();
		const T int_max = std::numeric_limits<T>::max();
		const T s1 = internal_;
		const T s2 = other.internal_;
		bool overflow = ((s1 > 0) && (s2 > 0) && (s1 > (int_max - s2))) | ((s1 < 0) && (s2 < 0) && (s1 < (int_min - s2)));
		if (overflow) {
			throw std::runtime_error("overflow");
		}
		return SafeSignedInt(internal_ + other.internal_);
	}

	SafeSignedInt operator/ (const SafeSignedInt& other) const {
		if (other.internal_ == 0) {
			throw std::runtime_error("division by zero");
		}
		return SafeSignedInt(internal_ / other.internal_);
	}

	//TODO check overflow in operators * and -

	operator T() const {
		return internal_;
	}

private:
	T internal_;
};




int main() {

	SafeSignedInt<int> a = 1;
	SafeSignedInt<int> b = 2;
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

	SafeSignedInt<char> c1 = 100;
	SafeSignedInt<char> c2 = 27;
	assert(127 == c1 + c2);

	c1 = 100;
	c2 = 100;
	try {
		c1 + c2;
		assert(false);
	} catch (const std::exception& e) {
		assert(std::string("overflow") == e.what());
	}

	// SafeSignedInt<float> afloat; // run time failure
	// SafeSignedInt<unsigned char> uchar; // run time failure
	
	return 0;
}


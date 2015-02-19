
#pragma once

#include <string>

template <class E>
struct Enum {
	static E from_string(const std::string&);
	static std::string to_string(const E&);
};

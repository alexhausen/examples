#include "enum2.hpp"

#include <iostream>
#include <sstream>
#include <vector>

enum class Fruit { Banana, Apple, Grape };
static const char* fruit_strings[] = { "banana", "apple", "grape" };

template <>
Fruit Enum<Fruit>::from_string(const std::string& s) {
	int fruit_strings_size = sizeof(fruit_strings)/sizeof(fruit_strings[0]);
	for (auto i = 0; i < fruit_strings_size; ++i) {
		if (s == fruit_strings[i]) {
			return static_cast<Fruit>(i);
		}
	}
	throw "wrong fruit name";
}

template <>
std::string Enum<Fruit>::to_string(const Fruit& f) {
	return std::string(fruit_strings[static_cast<int>(f)]);
}

std::ostream& operator<<(std::ostream& stream, const Fruit& fruit) {
	stream << Enum<Fruit>::to_string(fruit);
	return stream;
}

int main() {
	std::vector<Fruit> fruits = { Fruit::Banana, Fruit::Apple, Fruit::Apple, Fruit::Grape };
	for (const auto& f : fruits) {
		std::cout << f << std::endl;
	}

	std::string fruit_name = Enum<Fruit>::to_string(Fruit::Banana);
	std::cout << fruit_name << std::endl;

	Fruit f = Enum<Fruit>::from_string("grape");
	std::cout << static_cast<int>(f) << std::endl;
}

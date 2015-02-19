#include <string>
#include <iostream>

enum class color { red, green, blue };

std::string to_string(const color& c) {
        static const char* colors_str[] = { "red", "green", "blue" };
        return colors_str[static_cast<int>(c)];
}

std::ostream& operator<<(std::ostream& s, const color& c) {
	s << to_string(c);
	return s;
}

int main() {

	color x = color::red;
	std::cout << x << std::endl;

	
	
}


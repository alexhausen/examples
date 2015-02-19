#include <string>
#include <cassert>

int main() {

	std::string input1("abc,def");
	size_t pos1 = input1.find(',');
	assert(pos1 != std::string::npos);
	std::string n1(input1, 0, pos1);
	assert(n1 == "abc");
	std::string v1(input1, pos1 + 1);
	assert(v1 == "def");

	std::string input2("a,");
	size_t pos2 = input2.find(',');
	assert(pos2 != std::string::npos);
	std::string n2(input2, 0, pos2);
	assert(n2 == "a");
	std::string v2(input2, pos2 + 1);
	assert(v2.empty());

	std::string input3("a");
	size_t pos3 = input3.find(',');
	assert(pos3 == std::string::npos);

	std::string input4(",");
	size_t pos4 = input4.find(',');
	assert(pos4 == 0);

	return 0;
}


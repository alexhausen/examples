#include <algorithm>
#include <functional>
#include <locale>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cassert>

using namespace std;

string to_lower(string s, const locale loc) {
	transform(s.begin(), s.end(), s.begin(), [loc](char c){ return tolower(c, loc); });
	return s;
}

int main() {
	
	string s = to_lower("ABC", locale(""));
	cout << s << endl;
	assert("abc" == s);

	try {
		s = to_lower(u8"XYZ", locale("en_US.utf8"));
		cout << s << endl;
		assert("xyz" == s);
	} catch (const runtime_error& e) {
		//may throw runtime_error message: "locale::facet::_S_create_c_locale
		//name not valid" for some locales.
		//run locale --all
		cout << e.what() << endl;
	}

	return 0;
}


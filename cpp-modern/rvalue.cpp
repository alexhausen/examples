#include <iostream>
#include <string>

using namespace std;

void f(const string& s1) {
	string s2{s1}; // faz cópia
	s2[0] = 'x';
	cout << "f: " << s2 << endl;
}

void g(string&& s1) {
	string s2{s1}; // faz cópia
	s2[0] = 'x';
	cout << "g: " << s2 << endl;
}

void h(string&& s1) {
	string s2{std::move(s1)}; //não faz cópia, move o valor
	s2[0] = 'x';
	cout << "h: " << s2 << endl;
}

void i(string s1) {
	s1[0] = 'x';
	cout << "i: " << s1 << endl;
}


int main() {
	
	string s = {"String1"};
	
	f(s);
	cout << "after f: " << s << endl;
	//f("não compila");
	
	g(std::move(s));
	cout << "after g: " << s << endl;
	
	h(std::move(s));
	cout << "after h: " << s << endl; // s vazio
	
	i("Blah"); // compilador vai mover a string ao invés de fazer uma cópia pq é um rvalue

	return 0;
}


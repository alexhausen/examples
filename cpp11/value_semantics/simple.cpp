// simple example from presentation

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

void draw(const int& o, ostream& out, size_t position) {
        out << string(position, ' ') << o << endl;
}

class object {
public:
	object(const int& x) : obj_(new int_model(x)) { cout << "ctor" << endl; } 

	object(const object& x) : obj_(new int_model(*x.obj_)) { cout << "copy" << endl; }

	object(object&& x) = default; // default move constructor

	object& operator=(object x) { obj_ = move(x.obj_); return *this; }
	
	friend void draw(const object& x, ostream& out, size_t position) {
		x.obj_->draw_(out, position);
	}
	
private:
	struct int_model {
		int_model(const int& x) : data_(x) {}
		void draw_(ostream& out, size_t position) const {
			draw(data_, out, position);
		}
		int data_;
	};

	unique_ptr<int_model> obj_;
};

//using object = int;
//typedef int object;
//using document = vector<object>;

typedef vector<object> document;

void draw(const document& d, ostream& out, size_t position) {
	out << string(position, ' ') << "<document>" << endl;
	for (auto& o : d) draw(o, out, position + 2);
	out << string(position, ' ') << "</document>" << endl;
}

int main() {
	document doc1;
	doc1.reserve(5);
	doc1.emplace_back(0);
	doc1.emplace_back(1);
	doc1.emplace_back(2);
	doc1.emplace_back(3);

	reverse(doc1.begin(), doc1.end());

	draw(doc1, cout, 0);
}

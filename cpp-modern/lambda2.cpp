// http://herbsutter.com/2011/05/20/my-lambdas-talk-nwcpp-is-now-online/

#include <iostream>
#include <functional>

// a function object
struct mul_factory
{
    mul_factory(int scale) : factor(scale) {}

    std::function<int(int)> create() {
        return [=](int x){ return x * factor; };
    }

 private:
    int factor;
};

int main () {
	auto times3 = mul_factory(3).create();
	int twelve = times3(4);   // BOOM (????)
	std::cout << twelve << std::endl;
}


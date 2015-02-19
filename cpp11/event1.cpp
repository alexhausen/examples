#include <iostream>

class Event {
public:
	Event() { }

	Event(const Event&) = delete;

	Event& operator=(const Event&) = delete;

	virtual ~Event() { }

	virtual void exec() ;
};

class EventX : public Event {
public:
	virtual ~EventX() { }

	virtual void exec() {
		std::cout << "do x" << std::endl;
	}
};

int main() {
	EventX e1;
	e1.exec();

	return 0;
}


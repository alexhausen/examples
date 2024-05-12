
all: parser test

parser: parser.cpp parser.h main.cpp
	g++ -o parser -std=gnu++11 -Wall -Wextra -Wpedantic -Werror parser.cpp main.cpp

test: parser.cpp parser.h parser_test.cpp
	g++ -o test -std=gnu++11 -Wall -Wextra -Wpedantic -Werror parser.cpp parser_test.cpp -L/usr/local/lib -lgmock -lgmock_main -pthread

clean:
	/bin/rm -f parser.exe test.exe
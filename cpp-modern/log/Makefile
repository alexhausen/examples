all: main test

main: main.o log.o
	g++ -std=c++0x -O2 -o main main.o log.o -pthread

main.o: main.cpp log.h
	g++ -std=c++0x -c main.cpp

test: test.o log.o
	g++ -std=c++0x -o test test.o log.o  -L ~/Software/gmock-1.7.0/gtest/lib/.libs -lgtest -lgtest_main -pthread

log.o: log.cpp log.h
	g++ -std=c++0x -c -Wall -Wextra -Werror log.cpp #-DLOG_LEVEL=1 #-DNLOG

test.o: test.cpp log.h
	g++ -std=c++0x -c -Wall -Wextra -Werror test.cpp -I ~/Software/gmock-1.7.0/gtest/include

clean:
	rm -f main main.o test test.o log.o 
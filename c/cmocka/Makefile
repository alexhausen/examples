all: 	production.exe test_production.exe

CFLAGS=-std=c99 -Wall -Werror
LIB_TEST=cmocka
LIB_TEST_DIR="c:\Program Files (x86)\cmocka\bin"
INC_TEST_DIR="c:\Program Files (x86)\cmocka\include"

production.exe: main_production.o production.o dependency.o
	gcc -o production.exe main_production.o production.o dependency.o

main_production.o: main_production.c production.h
	gcc -c $(CFLAGS) main_production.c

production.o: production.c production.h dependency.h
	gcc -c $(CFLAGS) production.c

dependency.o: dependency.c dependency.h
	gcc -c $(CFLAGS) dependency.c

test_production.exe: test_production.o production.o
	gcc -o test_production.exe -L$(LIB_TEST_DIR) -l$(LIB_TEST) test_production.o production.o

test_production.o: test_production.c  production.h
	gcc -c $(CFLAGS) -I$(INC_TEST_DIR) test_production.c

clean:
	rm -f production.exe test_production.exe main_production.o production.o test_production.o dependency.o *.xml

all:
	g++ -g3 -Wall -Wextra -fPIC -c NumArray.cpp -I /usr/include/lua5.1 -llua5.1
	g++ -shared -Wl,-soname,libluaarray.so.1 -o libluaarray.so.1.0.1 NumArray.o

clean:
	rm -f libluaarray.so.1.0.1 NumArray.o

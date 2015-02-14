all:
	g++ -Wall -Wextra -fPIC -c ldir.cpp -I /usr/include/lua5.1/ -llua5.1
	g++ -shared -Wl,-soname,libluadir.so.1 -o libluadir.so.1.0.1 ldir.o

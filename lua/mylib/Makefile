#CPP=g++
#INC=-I /usr/include/lua5.1
#LIB=-L /usr/lib/x86_64-linux-gnu -llua5.1

CPP=/opt/intelbras/usr/bin/arm-unknown-linux-uclibcgnueabi-c++
INC=-I ~/Projects/certi_sipphone/.build_certi_platwip/prebuilt/host/usr/arm-unknown-linux-uclibcgnueabi/sysroot/usr/include
LIB=-L ~/Projects/certi_sipphone/.build_certi_platwip/prebuilt/target/usr/lib -lliblua

all: libmylib.so

libmylib.so: mylib.o
	$(CPP) -shared -Wl,-soname,libmylib.so -o libmylib.so mylib.o

mylib.o: mylib.cpp
	$(CPP) -Wall -Wextra -fPIC -c mylib.cpp $(INC) $(LIB)

clean:
	rm -f libmylib.so mylib.o


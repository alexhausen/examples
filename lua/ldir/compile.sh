#!/bin/sh
gcc ldir.c -I /usr/include/lua5.1/ -llua5.1 -shared -fPIC -o dir.so

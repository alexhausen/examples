#!/bin/sh -x
CC=/opt/intelbras/usr/bin/arm-unknown-linux-uclibcgnueabi-cc
${CC} -o test1 -O0 -g3 test.c -ldl -pthread
${CC} -fPIC -O0 -g3 -shared -o libtest.so lib.c -pthread


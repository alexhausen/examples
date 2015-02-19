#!/bin/sh -x
g++ -c -Wall -Wextra snd.cpp
g++ -c -Wall -Wextra wav2pcmu.cpp
g++ -o wav2pcmu wav2pcmu.o snd.o -lsndfile
g++ -c -O3 -Wall -Wextra ring2pcmu.cpp
g++ -o ring2pcmu ring2pcmu.o snd.o -lsndfile


CC = g++
CFLAGS = -Wall -Wextra -D_GLIBCXX_DEBUG -O3 -std=c++0x

all: argparse.o

argparse.o: argparse.cpp
	rm argparse.o -f
	rm argparse.hpp.gch -f
	$(CC) $(CFLAGS) -c argparse.cpp argparse.hpp

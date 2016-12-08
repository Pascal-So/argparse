CC = g++
CFLAGS = -Wall -Wextra -D_GLIBCXX_DEBUG -O3 -std=c++0x

all: argparse.o

argparse.o: argparse.cpp argparse.hpp
	$(CC) $(CFLAGS) -c argparse.cpp argparse.hpp

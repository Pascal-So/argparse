CC = g++
CFLAGS = -Wall -Wextra -D_GLIBCXX_DEBUG -O3 -std=c++0x

all: argparse.o

argparse.o: argparse.cpp argparse.hpp clear
	$(CC) $(CFLAGS) -c argparse.cpp argparse.hpp


clear:
	rm *.gch -f
	rm *.o -f

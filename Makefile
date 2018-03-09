CC = g++
CCFLAGS = -O3 -Wall -Wextra -pedantic -std=c++11

make: binary cleanup

dnest:
	make noexamples -C DNest4/code

objects:
	$(CC) $(CCFLAGS) -c src/main.cpp

binary: objects dnest
	$(CC) $(CCFLAGS) -L DNest4/code -o main *.o -ldnest4 -lpthread

cleanup:
	rm -f *.o


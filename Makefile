CC = g++
CCFLAGS = -O3 -Wall -Wextra -pedantic -std=c++11 -I include

make: binary cleanup

dnest:
	make noexamples -C DNest4/code

objects:
	$(CC) $(CCFLAGS) -c src/Data.cpp
	$(CC) $(CCFLAGS) -c src/main.cpp
	$(CC) $(CCFLAGS) -c src/MyConditionalPrior.cpp
	$(CC) $(CCFLAGS) -c src/MyModel.cpp

binary: objects dnest
	$(CC) $(CCFLAGS) -L DNest4/code -o main *.o -ldnest4 -lpthread

cleanup:
	rm -f *.o


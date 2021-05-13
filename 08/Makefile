CC = g++
FLAGS = -std=c++17 -Wall -pedantic -pthread

all: main.o 
	$(CC) $(FLAGS) main.o -o main

main.o: main.cpp thread_pool.h  
	$(CC) $(FLAGS) main.cpp -c

test: all 
	./main


clean:
	rm -f *.o
	rm -f main

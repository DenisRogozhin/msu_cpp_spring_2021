CC = g++
FLAGS = -std=c++17 -Wall -pedantic

all: allocator.o main.o
	$(CC) $(FLAGS) allocator.o main.o -o main

allocator.o: allocator.cpp allocator.h
	$(CC) $(FLAGS) allocator.cpp -c

main.o: allocator.o main.cpp  
	$(CC) $(FLAGS) main.cpp -c

test: all 
	./main


clean:
	rm -f *.o
	rm -f main

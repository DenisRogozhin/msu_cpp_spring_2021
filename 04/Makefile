CC = g++
FLAGS = -std=c++17 -Wall -pedantic

all: BigInt.o main.o
	$(CC) $(FLAGS) BigInt.o main.o -o main

BigInt.o: BigInt.cpp BigInt.h
	$(CC) $(FLAGS) BigInt.cpp -c

main.o: BigInt.o main.cpp  
	$(CC) $(FLAGS) main.cpp -c

test: all 
	./main


clean:
	rm -f *.o
	rm -f main

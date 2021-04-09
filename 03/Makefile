CC = g++
FLAGS = -std=c++17 -Wall -pedantic

all: matrix.o main.o
	$(CC) $(FLAGS) matrix.o main.o -o main

parser.o: matrix.cpp matrix.h
	$(CC) $(FLAGS) matrix.cpp -c

main.o: matrix.o main.cpp  
	$(CC) $(FLAGS) main.cpp -c

test: all 
	./main


clean:
	rm -f *.o
	rm -f main

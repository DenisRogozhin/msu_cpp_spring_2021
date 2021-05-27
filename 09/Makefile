CC = g++
FLAGS = -std=c++17 -pthread -Wall -pedantic

all: filesort.o main.o
	$(CC) $(FLAGS) filesort.o main.o -o main

filesort.o: filesort.cpp filesort.h
	$(CC) $(FLAGS) filesort.cpp -c

main.o: filesort.o main.cpp  
	$(CC) $(FLAGS) main.cpp -c

test: all 
	./main


clean:
	rm -f *.o
	rm -f main

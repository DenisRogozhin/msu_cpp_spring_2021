CC = g++
FLAGS = -std=c++17 -Wall -pedantic

all: main.o
	$(CC) $(FLAGS) main.o -o main

main.o: main.cpp  
	$(CC) $(FLAGS) main.cpp -c

test: all 
	./main


clean:
	rm -f *.o
	rm -f main

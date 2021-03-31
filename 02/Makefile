CC = g++
FLAGS = -std=c++17 -Wall -pedantic

all: parser.o main.o
	$(CC) $(FLAGS) parser.o main.o -o main

parser.o: parser.cpp parser.h
	$(CC) $(FLAGS) parser.cpp -c

main.o: parser.o main.cpp  
	$(CC) $(FLAGS) main.cpp -c

test: all 
	./main


clean:
	rm -f *.o
	rm -f main

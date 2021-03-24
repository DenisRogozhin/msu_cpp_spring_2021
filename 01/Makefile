CC = g++
FLAGS = -std=c++17 -Wall -pedantic

test: main.o 
	./main


hw1.o: hw1.cpp hw1.h
	$(CC) $(FLAGS) hw1.cpp -c

main.o: hw1.o main.cpp  
	$(CC) $(FLAGS) main.cpp -c
	$(CC) $(FLAGS) hw1.o main.o -o main


clean:
	rm -f *.o
	rm -f main

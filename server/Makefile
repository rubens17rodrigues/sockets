all: fibonacci.o
	clear
	gcc -Wall fibonacci.o main.c -o main

fibonacci.o: fibonacci.h
	gcc -Wall -c fibonacci.c

clean:
	rm -rf *.o

run:
	clear
	./main


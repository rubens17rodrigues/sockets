all: fibonacci.o
	gcc -Wall fibonacci.o main.c -o main
	rm -rf *.o

fibonacci.o: fibonacci.h
	gcc -Wall -c fibonacci.c

clean:
	rm -rf *.o

run:
	./main

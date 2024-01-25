all: A2

A2: a2.o
	gcc -Wall -g -std=c11 a2.o -o a2

a2.o: A2.c
	gcc -Wall -c -g -std=c11 A2.c

clean:
	rm *.o a2
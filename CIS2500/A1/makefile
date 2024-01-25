debylZoeA1: debylZoeA1.o main.o
	gcc -Wall -std=c99 debylZoeA1.o main.o -o debylZoeA1

debylZoeA1.o: debylZoeA1.c debylZoeA1.h
	gcc -Wall -std=c99 -c debylZoeA1.c
 
main.o: main.c debylZoeA1.h
	gcc -Wall -std=c99 -c main.c

clean:
	rm *.o debylZoeA1
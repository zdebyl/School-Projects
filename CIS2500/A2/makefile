debylZoeA2: debylZoeA2.o main.o
	gcc -Wall -std=c99 debylZoeA2.o main.o -o bin/noStringsAttached

debylZoeA2.o: src/debylZoeA2.c include/debylZoeA2.h
	gcc -Wall -std=c99 -c src/debylZoeA2.c
 
main.o: src/main.c include/debylZoeA2.h 
	gcc -Wall -std=c99 -c src/main.c

clean:
	rm *.o bin/noStringsAttached
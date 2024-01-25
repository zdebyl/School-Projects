CC=clang
CFLAGS= -Wall -std=c99 -pedantic
LDFLAGS=-L.

all: libmol.so _molecule.so molecule.py

mol.o: mol.c mol.h
	$(CC) $(CFLAGS) -c mol.c -fPIC -o mol.o

molecule_wrap.c molecule.py: molecule.i mol.h
	swig -python molecule.i

molecule_wrap.o: molecule_wrap.c
	$(CC) $(CFLAGS) -I/usr/include/python3.7m -c molecule_wrap.c -fPIC -o molecule_wrap.o

molecule.o: molecule.py
	$(CC) $(CFLAGS) -c molecule.py -o molecule.o

libmol.so: mol.o
	$(CC) mol.o -shared -o libmol.so

_molecule.so: molecule_wrap.o
	$(CC) $(CFLAGS) -shared molecule_wrap.o -L. -L/usr/include/python3.7m/config-3.7m-x86_64-linux-gnu -lpython3.7m -lmol -dynamiclib -o _molecule.so

clean:
	rm -f *.o *.so a2
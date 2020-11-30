CC = gcc
CFLAGS = -Wall -g -fpic

liblwp.so: lwp.o magic.o
	$(CC) -fpic -shared -o liblwp.so lwp.o magic.o

lwp.o: lwp.c
	$(CC) -fpic -Wall -c lwp.c

magic.o: magic64.S
	$(CC) -fpic -o magic.o -c magic64.S

clean:
	rm *.o *.so

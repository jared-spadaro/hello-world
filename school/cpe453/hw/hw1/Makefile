CC = gcc

CFLAGS = -Wall -g -fpic

intel-all: lib/libmalloc.so lib64/libmalloc.so archive

malloc: intel-all
	echo finished creating libraries

lib/libmalloc.so: lib malloc32.o
	$(CC) $(CFLAGS) -m32 -shared -o $@ malloc32.o

lib64/libmalloc.so: lib64 malloc64.o
	$(CC) $(CFLAGS) -shared -o $@ malloc64.o

lib:
	mkdir lib

lib64:
	mkdir lib64

malloc32.o: malloc.c
	$(CC) $(CFLAGS) -m32 -c -o malloc32.o malloc.c

malloc64.o: malloc.c
	$(CC) $(CFLAGS) -m64 -c -o malloc64.o malloc.c

archive: libmalloc.a libmalloc64.a

libmalloc.a:  malloc32.o
	ar r libmalloc.a malloc32.o

libmalloc64.a:  malloc64.o
	ar r libmalloc64.a malloc64.o

setdebug:
	source setdebug

clean:
	rm -r lib lib64 *.o *.a

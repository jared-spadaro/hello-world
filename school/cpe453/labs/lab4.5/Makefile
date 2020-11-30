CC = gcc
CFLAGS = -Wall 

mksuid: mksuid.o
	$(CC) -o mksuid mksuid.o -lcrypt

mksuid.o: mksuid.c
	$(CC) $(CFLAGS) -c mksuid.c -lcrypt

clean:
	rm *.o 

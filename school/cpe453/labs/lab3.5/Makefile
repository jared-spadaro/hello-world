CC = gcc
CFLAGS = -Wall 

mksuid: mksuid.o
	$(CC) -o mksuid mksuid.o -lcrypt
	chmod 04550 mksuid
	chown root mksuid

mksuid.o: mksuid.c
	$(CC) $(CFLAGS) -c mksuid.c -lcrypt

clean:
	rm *.o 

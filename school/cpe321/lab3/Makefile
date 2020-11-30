CC = gcc
CFLAGS = -Wall 

all: mksuid

mksuid: mksuid.c
	@$(CC) -o mksuid mksuid.c -lcrypt

clean:
	@rm -f mksuid *.o 

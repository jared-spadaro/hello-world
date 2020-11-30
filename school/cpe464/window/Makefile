# Makefile for asgn3

CC= g++
CFLAGS= -g

LIBS = -L. -lcpe464.2.15

all: window

window: window.o udp.o
	@$(CC) $(CFLAGS) -o window window.o udp.o $(LIBS)

window.o: window.c
	@$(CC) $(CFLAGS) -c window.c $(LIBS)

udp.o: udp.c
	@$(CC) $(CFLAGS) -c udp.c $(LIBS)

clean:
	@rm -f window *.o




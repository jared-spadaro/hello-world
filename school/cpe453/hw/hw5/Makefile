CC = gcc
CFLAGS = -Wall

all: minget.o minls.o
	@$(CC) -o minget minget.c
	@$(CC) -o minls minls.c

minget: minget.o
	@$(CC) -o minget minget.o

minls: minls.o
	@$(CC) -o minls minls.o

minget.o: minget.c
	@$(CC) $(CFLAGS) -c minget.c

minls.o: minls.c
	@$(CC) $(CFLAGS) -c minls.c

clean:
	@rm *.o 

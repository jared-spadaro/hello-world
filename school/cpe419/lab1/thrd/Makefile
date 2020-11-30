CC = gcc
CFLAGS = -Wall -lrt -lpthread

all: create mult

create: create.o
	@$(CC) -o create create.o

mult: mult.o
	@$(CC) $(CFLAGS) -o mult mult.o

create.o: create.c
	@$(CC) $(CFLAGS) -c create.c

mult.o: mult.c
	@$(CC) $(CFLAGS) -c mult.c

clean:
	@rm -f *.o matrix1 matrix2 result create mult

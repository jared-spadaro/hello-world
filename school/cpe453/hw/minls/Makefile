CC = gcc
CFLAGS = -Wall

minls: minls.o
	@$(CC) -o minls minls.o

minls.o: minls.c
	@$(CC) $(CFLAGS) -c minls.c

clean:
	@rm *.o 

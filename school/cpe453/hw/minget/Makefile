CC = gcc
CFLAGS = -Wall

minget: minget.o
	@$(CC) -o minget minget.o

minget.o: minget.c
	@$(CC) $(CFLAGS) -c minget.c

clean:
	@rm *.o 

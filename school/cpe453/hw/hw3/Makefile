CC = gcc
CFLAGS = -Wall 

dine: dine.o
	$(CC) -o dine dine.o -lpthread

dine.o: dine.c
	$(CC) $(CFLAGS) -c dine.c -lpthread

clean:
	rm *.o 

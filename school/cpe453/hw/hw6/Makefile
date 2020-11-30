CC = gcc
CFLAGS = -Wall -ansi -pedantic

hello: hello.o
	@$(CC) -o hello hello.o 

test: hello
	@./hello

hello.o: hello.c 
	@$(CC) $(CFLAGS) -c -o hello.o hello.c

clean:
	@rm *.o 

CC = gcc
CFLAGS = -Wall -fno-stack-protector 

all: smashme configure

smashme: smashme.c
	@$(CC) $(CFLAGS) -o smashme smashme.c

configure: configure.c
	@$(CC) $(CFLAGS) -o configure configure.c

clean:
	@rm -f smashme configure *.o

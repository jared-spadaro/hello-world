CC = gcc
CFLAGS = -Wall

all: vig ftable

vig: vig.c
	@$(CC) $(CFLAGS) -o vig vig.c 

ftable: ftable.c
	@$(CC) $(CFLAGS) -o ftable ftable.c -lm

clean:
	@rm -f vig ftable

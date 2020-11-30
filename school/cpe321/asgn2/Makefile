CC = gcc
CFLAGS = -Wall

all: kasiski ftable ic vig

vig: vig.c
	@$(CC) $(CFLAGS) -o vig vig.c

kasiski: kasiski.c
	@$(CC) $(CFLAGS) -o kasiski kasiski.c -lm

ftable: ftable.c
	@$(CC) $(CFLAGS) -o ftable ftable.c -lm

ic: ic.c
	@$(CC) $(CFLAGS) -o ic ic.c

clean:
	@rm -f vig kasiski ftable ic *.o

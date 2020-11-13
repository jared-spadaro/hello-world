CC = gcc
CFLAGS = -Wall -ansi -pedantic
TARGET = pyth

$(TARGET): $(TARGET).c
	@$(CC) -o $(TARGET) $(TARGET).c

clean:
	@rm -f *.o $(TARGET)

test:
	@rm -f *.o $(TARGET)
	@$(CC) -o $(TARGET) $(TARGET).c
	@./$(TARGET)


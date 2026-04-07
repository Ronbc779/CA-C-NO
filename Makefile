# Compiler
CC = gcc

# Enable warnings for debugging
CFLAGS = -Wall -g

#exe name
TARGET = casino

# files used in project (currently)
SRCS = casino.c blackjack.c menu_functions.c guess.c

# Rule to build the project
all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

# Rule to delete the executable (useful for a fresh start)
clean:
	rm -f $(TARGET)
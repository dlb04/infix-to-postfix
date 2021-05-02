CC := gcc
CFLAGS := -g -Wall -Wextra -std=c11 -pedantic

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)

itop: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
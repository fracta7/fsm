CC = gcc
FL = -Wall -Werror -Wextra -std=c11

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: re main

main: $(OBJ)
	$(CC) $(FL) $(OBJ) -o main -lncurses

%.o: %.c
	$(CC) $(FL) -c $< -o $@

re: clean

clean:
	rm -rf main *.o

.PHONY: all re clean

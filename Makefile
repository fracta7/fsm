CC = gcc
FL = -Wall -Werror -Wextra -std=c11 -lncurses

all: re main

main: main.o frontend.o
	$(CC) $(FL) main.o frontend.o -o main -lncurses

main.o: main.c frontend.h
	$(CC) $(FL) -c main.c -o main.o -lncurses

frontend.o: frontend.c frontend.h
	$(CC) $(FL) -c frontend.c -o frontend.o

re: clean

clean:
	rm -rf main *.o

.PHONY: all re clean

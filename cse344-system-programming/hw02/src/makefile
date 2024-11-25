CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11

all: main


main: main.c
	$(CC) $(CFLAGS) -o main main.c


valgrind: $(main)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --gen-suppressions=all -s ./main

clean:
	rm -f main  log_* *.o
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11

all: main


main: main.c
	$(CC) $(CFLAGS) -o pCp main.c -lpthread


valgrind: $(main)
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --gen-suppressions=all -s ./pCp

clean:
	rm -f pCp *.o
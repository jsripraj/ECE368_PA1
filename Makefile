# ECE368 PA1 Makefile

CFLAGS = -Werror -Wall -Wshadow -O3 -std=c99
GCC = gcc $(CFLAGS)

all: sorting.o main.o
	$(GCC) sorting.c main.c -o proj1

%.o: %.c sorting.h
	$(GCC) -c $<

test: all
	./proj1 i given_files/15.b test_seq test_output

clean:
	/bin/rm -f *.o
	/bin/rm -f proj1
	/bin/rm -f test_output test_seq

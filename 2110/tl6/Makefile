# Makefile for CS 2110 Timed Lab 6 (Student Version)
# Fall 2016
# Author: Sanjay Sood & Patrick Tam

CC = gcc
CFLAGS = -std=gnu99 -pedantic -Wall -Werror -Wextra -g
VALOPTS = --leak-check=yes --show-reachable=yes --tool=memcheck

all:	list.c tests.c list.h
	$(CC) $(CFLAGS) tests.c list.c -o tests

clean:
	rm -f tests *.o

run-valgrind : clean all
	valgrind $(VALOPTS) ./tests

run-tests : clean all
	./tests

run-gdb: clean all
	gdb ./tests

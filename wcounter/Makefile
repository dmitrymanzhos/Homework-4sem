.PHONY: all clean

CC = gcc
CFLAGS = -O -Wall -g

all: wcounter

wcounter: wcounter.o parser.o dictionary.o
	$(CC) wcounter.o parser.o dictionary.o -o wcounter $(CFLAGS)

wcounter.o: wcounter.c
	$(CC) $? -c $(CFLAGS)

parcer.o: parser.c
	$(CC) $? -c $(CFLAGS)

dictionary.o: dictionary.c
	$(CC) $? -c $(CFLAGS)

clear:
	rm -rf test *.o

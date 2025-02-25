.PHONY: all clean

CC = gcc
CFLAGS = -O -Wall -g

all: main

main: cat.o dog.o animal.o main.o
	$(CC) $^ -o $@ $(CFLAGS)

# main.o: main.c
# 	$(CC) $? -c $(CFLAGS)

# cat.o: cat.c
# 	$(CC) $? -c $(CFLAGS)

# dog.o: dog.c
# 	$(CC) $? -c $(CFLAGS)

clear:
	rm -rf main *.o

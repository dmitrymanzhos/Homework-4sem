.PHONY: all clean

CC = g++
CFLAGS = -O -Wall -g

all: main

main: tview.o  main.o  
	$(CC) $^ -o $@ $(CFLAGS)

clear:
	rm -rf main *.o

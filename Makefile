CFLAGS = -g -Wall
CC = gcc
all: sorter

sorter: sorter.o util.o
	$(CC) $(CFLAGS) -o sorter sorter.o util.o

sorter.o: sorter.c
	$(CC) $(CFLAGS) -c sorter.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

clean:  clean_sorter clean_util

clean_sorter:
	rm -f sorter.o
	rm -f sorter

clean_util:
	rm -f util.o


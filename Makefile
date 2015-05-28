CFLAGS = -g -Wall -I.
CC = gcc
all: sort_driver

sort_driver: sort_driver.o sorter.o util.o
	$(CC) $(CFLAGS) -o sort_driver sort_driver.o sorter.o util.o

sort_driver.o: sort_driver.c
	$(CC) $(CFLAGS) -c sort_driver.c

sorter.o: sorter.c sorter.h
	$(CC) $(CFLAGS) -c sorter.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

clean:  clean_sorter clean_util clean_sort_driver

clean_sorter:
	rm -f sorter.o

clean_util:
	rm -f util.o

clean_sort_driver:
	rm -f sort_driver.o
	rm -f sort_driver

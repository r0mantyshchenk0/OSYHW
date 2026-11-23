CC = gcc
EXTRA_CFLAGS =

all: forkpipe

forkpipe: forkpipe.c
	$(CC) -Wall $(EXTRA_CFLAGS) -o forkpipe forkpipe.c

clean:
	rm -f forkpipe

.PHONY: all clean

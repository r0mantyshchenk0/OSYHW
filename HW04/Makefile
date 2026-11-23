CC ?= gcc
EXTRA_CFLAGS ?= -fsanitize=address -fno-omit-frame-pointer
CFLAGS += -Wall -g -O2 $(EXTRA_CFLAGS) -pthread

all: factory

factory: factory.c
	$(CC) $(CFLAGS) factory.c -o factory

clean:
	rm -f factory

.PHONY: all clean

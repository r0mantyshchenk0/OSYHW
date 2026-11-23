CC = gcc
CFLAGS = -Wall -g -O2
EXTRA_CFLAGS ?= -fsanitize=address -fno-omit-frame-pointer

TARGET = prod-cons

all: $(TARGET)

$(TARGET): prod-cons.o
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -pthread -o $@ $^

prod-cons.o: prod-cons.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -pthread -c $< -o $@

clean:
	rm -f $(TARGET) *.o

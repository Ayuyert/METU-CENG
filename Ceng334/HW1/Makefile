CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = eshell.c parser.c
OBJS = $(SRCS:.c=.o)
TARGET = eshell

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

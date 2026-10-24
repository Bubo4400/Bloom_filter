CC = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla -Iinclude

SRCS := $(wildcard src/*.c)
OBJS := $(SRCS:.c=.o)
BIN = bloom_filter

.PHONY: all clean

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	$(RM) $(OBJS) $(BIN)

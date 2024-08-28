CC=gcc
CFLAGS=-g -Wall -Werror
LDFLAGS=-lm
HEADERS = mathneed.h gram.h LLL.h SE.h writefile.h
SOURCES = mathneed.c gram.c LLL.c SE.c writefile.c main.c
OBJECTS = $(SOURCES:.c=.o)

all: runme

runme: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o runme $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	chmod +x tests/test.sh
	cd tests && ./test.sh
clean:
	rm -f $(OBJECTS) runme
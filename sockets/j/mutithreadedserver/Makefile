CC=gcc
CFLAGS=-g -lpthread
$BINS=server

all:server

server:server.c
	$(CC)  -o server server.c $(CFLAGS)

clean:
	rm -rf *.dSYM $(BINS)

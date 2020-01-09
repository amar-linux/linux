CC=gcc
CFLAGS=-g
PTHREAD_LIBSABC=-lpthread
BINS=server
OBJS= server.o myqueue.o

all:$(BINS)

server: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(PTHREAD_LIBSABC)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(PTHREAD_LIBSABC)
	


clean:
	rm -rf *.dSYM $(BINS)

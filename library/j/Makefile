

CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-ldl
BINS=libplus1.so libplus2.so test.elf  #for mac use .dylib and not .so, and to create .elf file on linux you have to add -ldl comilation flag to gcc 

all: $(BINS)

%.so: %.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $^

%.elf: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)       

clean:
	rm $(BINS)
	rm -r *.elf 
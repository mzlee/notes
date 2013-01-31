SPLOITS = epfb shell simple simple32
CFLAGS = -g
LDFLAGS = -lc
CC = gcc
LD = gcc

all: $(SPLOITS)
install: all

epfb: CFLAGS+=-std=c99
epfb: evince-ps-field-bof.o
	$(LD) $< -o $@
simple: CFLAGS+=-fno-stack-protector
simple32: CFLAGS+=-m32 -fno-stack-protector
simple32: simple.c
	$(CC) -o $@ $(CFLAGS) -D__32_BIT $<

clean:
	rm -f *.o $(SPLOITS)

SPLOITS = epfb shell simple
CFLAGS = -g -lc
CC = gcc
LD = gcc

all: $(SPLOITS)
install: all

epfb: CFLAGS+=-std=c99
epfb: evince-ps-field-bof.o
	$(LD) $< -o $@
simple: CFLAGS+=-std=c99 -fno-stack-protector

clean:
	rm -f *.o $(SPLOITS)

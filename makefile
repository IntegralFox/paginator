CC=gcc
CFLAGS=-c -Wall -g
LFLAGS=-o bin/vmm

all: bin/vmm

bin/vmm: obj/vmm.o
	$(CC) $(LFLAGS) obj/vmm.o

obj/vmm.o: src/vmm.c
	$(CC) $(CFLAGS) -o obj/vmm.o src/vmm.c

clean:
	rm -rf bin/vmm obj/*

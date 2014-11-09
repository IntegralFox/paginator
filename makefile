CC=gcc
CFLAGS=-c -Wall -g
LFLAGS=-o bin/vmm

all: bin/vmm

bin/vmm: obj/vmm.o obj/paging.o
	$(CC) $(LFLAGS) obj/vmm.o obj/paging.o

obj/vmm.o: src/vmm.c
	$(CC) $(CFLAGS) -o obj/vmm.o src/vmm.c

obj/paging.o: src/paging.h src/paging.c
	$(CC) $(CFLAGS) -o obj/paging.o src/paging.c

clean:
	rm -rf bin/vmm obj/*

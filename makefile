CC=gcc
CFLAGS=-c -Wall -g
LFLAGS=-o bin/paginator

all: bin/paginator

bin/paginator: obj/paginator.o obj/paging.o obj/options.o obj/tlb.o
	$(CC) $(LFLAGS) obj/paginator.o obj/paging.o obj/options.o obj/tlb.o

obj/paginator.o: src/paginator.c
	$(CC) $(CFLAGS) -o obj/paginator.o src/paginator.c

obj/paging.o: src/paging.h src/paging.c
	$(CC) $(CFLAGS) -o obj/paging.o src/paging.c

obj/options.o: src/options.h src/options.c
	$(CC) $(CFLAGS) -o obj/options.o src/options.c

obj/tlb.o: src/tlb.h src/tlb.c
	$(CC) $(CFLAGS) -o obj/tlb.o src/tlb.c

clean:
	rm -rf bin/paginator obj/*

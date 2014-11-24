CC=gcc
CFLAGS=-c -Wall -g
LFLAGS=-o bin/paginator

all: bin obj bin/paginator

bin:
	mkdir bin

obj:
	mkdir obj

bin/paginator: obj/paginator.o obj/paging.o obj/options.o obj/tlb.o
	$(CC) $(LFLAGS) obj/paginator.o obj/paging.o obj/options.o obj/tlb.o

obj/paginator.o: src/paginator.c src/options.h src/paging.h src/tlb.h
	$(CC) $(CFLAGS) -o obj/paginator.o src/paginator.c

obj/paging.o: src/paging.h src/paging.c src/options.h
	$(CC) $(CFLAGS) -o obj/paging.o src/paging.c

obj/options.o: src/options.h src/options.c
	$(CC) $(CFLAGS) -o obj/options.o src/options.c

obj/tlb.o: src/tlb.h src/tlb.c
	$(CC) $(CFLAGS) -o obj/tlb.o src/tlb.c

clean:
	rm -rf bin/paginator obj/*

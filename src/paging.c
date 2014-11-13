/* Implementation of page related activites */

#include <stdlib.h>
#include <stdio.h>
#include "paging.h"
#include "options.h"
#include "globals.h"

FILE* backingStore;

struct Page {
	unsigned long frame;
	int valid;
};

struct Page* pageTable;

void initializePageTable() {
	pageTable = (struct Page*) calloc(opt.pageNum, sizeof(struct Page));
}

int openBackingStore(char* path) {
	return backingStore = fopen(path, "r");
}

void freePageTable() {
	free(pageTable);
	fclose(backingStore);
}

unsigned long pageTableFrame(unsigned long page) {
}

unsigned long pageOf(unsigned long address) {
	address = address & LOG_ADDR_MASK;
	address = address >> OFFSET_BITS;
	return address;
}

unsigned long offsetOf(unsigned long address) {
	address = address & OFFSET_MASK;
	return address;
}

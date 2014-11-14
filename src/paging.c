/* Implementation of page related activites */

#include <stdlib.h>
#include <stdio.h>
#include "paging.h"
#include "options.h"

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
	backingStore = fopen(path, "r");
	return (int) backingStore;
}

void freePageTable() {
	free(pageTable);
	fclose(backingStore);
}

void closeBackingStore() {
	fclose(backingStore);
}

unsigned long pageTableFrame(unsigned long page, char* physMem) {
	// Add logic
	return 0;
}

unsigned long pageOf(unsigned long address) {
	address = address >> opt.offsetBits;
	return address;
}

unsigned long offsetOf(unsigned long address) {
	address = address & opt.offsetMask;
	return address;
}

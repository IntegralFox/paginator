/* Implementation of page related activites */

#include <stdlib.h>
#include "paging.h"
#include "options.h"

struct Page* pageTable;

void initializePageTable() {
	pageTable = (struct Page*) calloc(opt.pageNum, sizeof(struct Page));
}

void freePageTable() {
	free(pageTable);
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

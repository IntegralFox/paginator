/* Implementation of page related activites */

#include <stdlib.h>
#include <stdio.h>
#include "paging.h"
#include "options.h"

struct Page {
	unsigned long frame;
	int valid;
};
struct Page* pageTable;
int* frameTable;

void initializePageTable() {
	pageTable = (struct Page*) calloc(opt.pageNum, sizeof(struct Page));
	frameTable = (int*) calloc(opt.frameNum, sizeof(int));
}

void freePageTable() {
	free(pageTable);
	free(frameTable);
}

unsigned long pageTableFrame(unsigned long page, char* physMem, FILE* backingStore) {
	unsigned long freeFrame;
	if (pageTable[page].valid) {
		return pageTable[page].frame;
	} else {
		freeFrame = findFreeFrame();
		copyPage(backingStore, page, physMem, freeFrame);
		pageTable[page].frame = freeFrame;
		pageTable[page].valid = 1;
		return freeFrame;
	}
}

unsigned long pageOf(unsigned long address) {
	address = address >> opt.offsetBits;
	return address;
}

unsigned long offsetOf(unsigned long address) {
	address = address & opt.offsetMask;
	return address;
}

void copyPage(FILE* backingStore, unsigned long page, char* physMem, unsigned long frame) {
	fseek(backingStore, page << opt.offsetBits, SEEK_SET);
	fread(physMem + (frame << opt.offsetBits), 1, opt.frameSize, backingStore);
}

unsigned long findFreeFrame() {
	unsigned long i;
	for (i = 0; i < opt.frameNum; ++i) {
		if (!frameTable[i]) {
			frameTable[i] = 1;
			return i;
		}
	}
	return victimizeFrame();
}

unsigned long victimizeFrame() {
	unsigned long i;
	printf("Needed a victim! This should not have happened!!!\n");
	// Select Frame
	// Set false
	// Invalidate page table entry
	return i;
}

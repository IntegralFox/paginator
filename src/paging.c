/* Implementation of page related activites */

#include <stdlib.h>
#include <stdio.h>
#include "paging.h"
#include "options.h"

FILE* backingStore;
int* frameTable;

struct Page {
	unsigned long frame;
	int valid;
};

struct Page* pageTable;

void initializePageTable() {
	pageTable = (struct Page*) calloc(opt.pageNum, sizeof(struct Page));
	frameTable = (int*) calloc(opt.frameNum, sizeof(int));
}

int openBackingStore(char* path) {
	backingStore = fopen(path, "r");
	return (int) backingStore;
}

void freePageTable() {
	free(pageTable);
	free(frameTable);
}

void closeBackingStore() {
	fclose(backingStore);
}

unsigned long pageTableFrame(unsigned long page, char* physMem) {
	unsigned long freeFrame;
	if (pageTable[page].valid) {
		return pageTable[page].frame;
	} else {
		freeFrame = findFreeFrame();
		copyPage(physMem, page, freeFrame);
		pageTable[page].frame = freeFrame;
		pageTable[page].valid = 1;
		return freeFrame;
	}
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

void copyPage(char* physMem, unsigned long page, unsigned long frame) {
	fseek(backingStore, frame << opt.offsetBits, SEEK_SET);
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
	// Select Frame
	// Set false
	// Invalidate page table entry
	return i;
}

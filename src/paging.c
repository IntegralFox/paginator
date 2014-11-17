/* Implementation of page related activites */

#include <stdlib.h>
#include "paging.h"
#include "options.h"

struct Page {
	unsigned long frame;
	int valid;
};
struct Page* pageTable;
struct Frame* frameTable;
unsigned long pageHits = 0, pageMisses = 0;

void initializePageTable() {
	pageTable = (struct Page*) calloc(opt.pageNum, sizeof(struct Page));
	frameTable = (struct Frame*) calloc(opt.frameNum, sizeof(struct Frame));
}

void freePageTable() {
	free(pageTable);
	free(frameTable);
}

unsigned long pageTableFrame(unsigned long page, char* physMem, FILE* backingStore) {
	unsigned long frame;
	if (pageTable[page].valid) {
		frame = pageTable[page].frame;
		++pageHits; // It's a page hit
	} else {
		frame = findFreeFrame();
		copyPage(backingStore, page, physMem, frame);
		pageTable[page].frame = frame;
		pageTable[page].valid = 1;
		++pageMisses; // It's a page miss
	}
	frameTable[frame].time = clock();
	return frame;
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
		if (!frameTable[i].valid) {
			frameTable[i].valid = 1;
			return i;
		}
	}
	return victimizeFrame();
}

unsigned long victimizeFrame() {
	unsigned long i, frame;
	clock_t time;

	// LRU replacement
	// Select the smallest time (least recently accessed)
	frame = 0;
	time = frameTable[0].time;
	for (i = 1; i < opt.frameNum; ++i) {
		if (frameTable[i].time < time) {
			frame = i;
			time = frameTable[i].time;
		}
	}

	// Invalidate the page in the page table
	for (i = 0; i < opt.pageNum; ++i) {
		if (pageTable[i].frame == frame) {
			pageTable[i].valid = 0;
			break;
		}
	}

	return frame;
}

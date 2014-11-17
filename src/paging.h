/* Header for page related activities */

#ifndef VMM_PAGING
#define VMM_PAGING

#include <stdio.h>
#include <time.h>

struct Frame {
	int valid;
	clock_t time;
};
extern struct Frame* frameTable;
extern unsigned long pageHits, pageMisses, pageVictims;

// Sets up the page table structures
void initializePageTable();

// Frees the page Table
void freePageTable();

// Returns a the frame for a page (and reads one in on miss)
unsigned long pageTableFrame(unsigned long, char*, FILE*);

// Gets the page number from a logical address
unsigned long pageOf(unsigned long);

// Gets the offset from a logical address
unsigned long offsetOf(unsigned long);

// Copies a page from the backing store into physical memory
void copyPage(FILE*, unsigned long, char*, unsigned long);

// Finds an open frame or victimizes one
unsigned long findFreeFrame();

// Selects a frame to victimize
unsigned long victimizeFrame();

#endif

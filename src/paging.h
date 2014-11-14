/* Header for page related activities */

#ifndef VMM_PAGING
#define VMM_PAGING

// Sets up the page table structures
void initializePageTable();

// Opens the backing store file to read into memory pages
int openBackingStore(char*);

// Frees the page Table
void freePageTable();

// closes the backing store
void closeBackingStore();

// Returns a the frame for a page (and reads one in on miss)
unsigned long pageTableFrame(unsigned long, char*);

// Gets the page number from a logical address
unsigned long pageOf(unsigned long);

// Gets the offset from a logical address
unsigned long offsetOf(unsigned long);

// Copies a page from the backing store into physical memory
void copyPage(char*, unsigned long, unsigned long);

// Finds an open frame or victimizes one
unsigned long findFreeFrame();

// Selects a frame to victimize
unsigned long victimizeFrame();

#endif

/* Operates and matains the TLB */

#ifndef VMM_TLB
#define VMM_TLB

#define TLB_SIZE 16

// Set up the tlb to be empty
void tlbInitialize();

// Returns a frame from the buffer for a page
// Or returns -1 on failure
unsigned long tlbFrame(unsigned long);

// Add a page/frame combo to the buffer
void tlbUpdate(unsigned long, unsigned long);

#endif


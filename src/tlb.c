/* Implentation of TLB */

#include "tlb.h"

struct TlbItem {
	unsigned long page;
	unsigned long frame;
	unsigned long valid;
};

struct TlbItem tlb[TLB_SIZE];

void tlbInitialize() {
	int i;
	for (i = 0; i < TLB_SIZE; ++i) {
		tlb[i].valid = 0;
	}
}

unsigned long tlbFrame(unsigned long page) {
	int i;
	for (i = 0; i < TLB_SIZE; ++i) {
		if (tlb[i].valid && tlb[i].page == page) {
			return tlb[i].frame;
		}
	}
	// Page not in buffer, return error of -1
	return -1;
}

void tlbUpdate(unsigned long page, unsigned long frame) {
	static int next = 0;
	tlb[next].page = page;
	tlb[next].frame = frame;
	tlb[next].valid = 1;
	next = (next + 1) % TLB_SIZE;
}


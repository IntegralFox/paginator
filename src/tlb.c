/* Implentation of TLB */

#include <stdio.h>
#include "options.h"
#include "tlb.h"
#include "paging.h"

struct TlbItem {
	unsigned long page;
	unsigned long frame;
	unsigned long valid;
};
struct TlbItem tlb[TLB_SIZE];
unsigned long tlbHits = 0, tlbMisses = 0;

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
			frameTable[tlb[i].frame].time = clock();
			++tlbHits; // It's a tlb hit
			++pageHits; // Therefore it's also a page hit
			if (opt.debug) {
				if (opt.printHex)
					printf("TLB hit 0x%2.2lX -> 0x%2.2lX\n", page, tlb[i].frame);
				else
					printf("TLB hit %li -> %li\n", page, tlb[i].frame);
			}
			return tlb[i].frame;
		}
	}
	// Page not in buffer, return error of -1
	++tlbMisses; // It's a tlb miss but not necessarily a page miss
	return -1;
}

void tlbUpdate(unsigned long page, unsigned long frame) {
	static int next = 0;
	tlb[next].page = page;
	tlb[next].frame = frame;
	tlb[next].valid = 1;
	next = (next + 1) % TLB_SIZE;
}

void tlbInvalidate(unsigned long frame) {
	int i;
	for (i = 0; i < TLB_SIZE; ++i) {
		if (tlb[i].frame == frame) {
			tlb[i].valid = 0;
			return;
		}
	}
}

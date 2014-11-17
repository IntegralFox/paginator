/* Main file for Virtual Memory Mapper
 * Author: Michael Welborn
 * Date: 2014-11-08 */

#include <stdio.h>
#include <stdlib.h>
#include "options.h"
#include "paging.h"
#include "tlb.h"

char* physMem;
FILE* addressList;
FILE* backingStore;

// Wrapper to resolve a page to a frame
unsigned long pageToFrame(unsigned long);

int main(int argc, char** argv) {
	unsigned long logicalAddress, physicalAddress, page, offset, frame, value;

	// Initialize some stuff
	parseOptions(&argc, &argv);

	// Exit if insufficient arguments
	if (argc < 2) {
		fprintf(stderr, "paginator: Insufficient arguments\nUsage: vmm backing_store_file address_file\n");
		return 0;
	}

	// Open the files and exit on failure
 	if ((backingStore = fopen(argv[0], "r")) == NULL) {
		fprintf(stderr, "paginator: %s: Cannot open backing store binary\n", argv[0]);
		return 0;
	}
 	if ((addressList = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "paginator: %s: Cannot open address file\n", argv[1]);
		fclose(backingStore);
		return 0;
	}

	// Allocate "physical" memory and management structs
	physMem = (char*) malloc(opt.frameSize * opt.frameNum);
	initializePageTable();
	tlbInitialize();

	// Do Stuff
	while (fscanf(addressList, "%ld", &logicalAddress) != EOF) {
		page = pageOf(logicalAddress);
		offset = offsetOf(logicalAddress);
		frame = pageToFrame(page);
		physicalAddress = (frame << opt.offsetBits) | offset;
		value = physMem[physicalAddress];
		if (opt.printHex) {
			printf("Virtual address: 0x%4.4lX Physical address: 0x%4.4lX Value: 0x%2.2X\n", logicalAddress, physicalAddress, value);
		} else {
			printf("Virtual address: %ld Physical address: %ld Value: %d\n", logicalAddress, physicalAddress, value);
		}
	}

	// Free all resources
	free(physMem);
	fclose(addressList);
	fclose(backingStore);
	freePageTable();

	// Show statistics
	printf("\n-- Statistics --\n");
	printf(" TLB hits: %-4ld   TLB misses: %-4ld  H/M Ratio: %-6.3f  Hit Percent: %ld%%\n",
		tlbHits, tlbMisses, ((double)tlbHits / (double)tlbMisses),
		(tlbHits * 100 / ((tlbHits + tlbMisses) * 100)));
	printf("Page hits: %-4ld  Page misses: %-4ld  H/M Ratio: %-6.3f  Hit Percent: %ld%%\n",
		pageHits, pageMisses, ((double)pageHits / (double)pageMisses),
		(pageHits * 100 / (pageHits + pageMisses)));

	return 0;
}

unsigned long pageToFrame(unsigned long page) {
	unsigned long frame;
	frame = tlbFrame(page);
	if (frame == -1) {
		frame = pageTableFrame(page, physMem, backingStore);
		tlbUpdate(page, frame);
	}
	return frame;
}

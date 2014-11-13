/* Main file for Virtual Memory Mapper
 * Author: Michael Welborn
 * Date: 2014-11-08 */

#include <stdio.h>
#include "options.h"
#include "paging.h"
#include "tlb.h"

// Wrapper to resolve a page to a frame
unsigned long pageToFrame(unsigned long);

int main(int argc, char** argv) {
	FILE* addressList;
	char* physMem;
	unsigned long address, page, offset, frame;

	// Initialize some stuff
	parseOptions(&argc, &argv);
	initializePageTable();

	// Exit if insufficient arguments
	if (argc < 2) {
		fprintf(stderr, "vmm: Insufficient arguments\nUsage: vmm backing_store_file address_file\n");
		return 0;
	}

	// Open the files and exit on failure
 	if (openBackingStore(argv[0])) {
		fprintf(stderr, "vmm: %s: Cannot open backing store binary\n", argv[0]);
		return 0;
	}
 	if ((addressList = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "vmm: %s: Cannot open address file\n", argv[1]);
		return 0;
	}

	// Allocate "physical" memory

	// Do Stuff
	while (fscanf(addressList, "%ld", &address) != EOF) {
		page = pageOf(address);
		offset = offsetOf(address);
		frame = pageToFrame(page);
		if (opt.printHex) {
			printf("0x%4.4lX -> 0x%2.2lX + 0x%2.2lX\n", address, page, offset);
		} else {
			printf("%ld -> %ld + %ld\n", address, page, offset);
		}
	}

	// Free all resources
	fclose(addressList);
	freePageTable();

	return 0;
}

unsigned long pageToFrame(unsigned long page) {
	unsigned long frame;
	frame = tlbFrame(page);
	if (frame == -1) {
		frame = pageTableFrame(page);
		tlbUpdate(page, frame);
	}
	return frame;
}

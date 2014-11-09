/* Main file for Virtual Memory Mapper
 * Author: Michael Welborn
 * Date: 2014-11-08 */

#include <stdio.h>
#include "options.h"
#include "paging.h"

int main(int argc, char** argv) {
	FILE* backingStore;
	FILE* addressList;
	unsigned long address, page, offset;

	// Parse option flags
	parseOptions(&argc, &argv);

	// Exit if insufficient arguments
	if (argc < 2) {
		fprintf(stderr, "vmm: Insufficient arguments\nUsage: vmm backing_store_file address_file\n");
		return 0;
	}

	// Open the files and exit on failure
 	if ((backingStore = fopen(argv[0], "r")) == NULL) {
		fprintf(stderr, "vmm: %s: Cannot open backing store binary\n", argv[1]);
		return 0;
	}
 	if ((addressList = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "vmm: %s: Cannot open address file\n", argv[2]);
		return 0;
	}

	// Do Stuff
	while (fscanf(addressList, "%ld", &address) != EOF) {
		page = pageOf(address);
		offset = offsetOf(address);
		if (printHex) {
			printf("0x%4.4lX -> 0x%2.2lX + 0x%2.2lX\n", address, page, offset);
		} else {
			printf("%ld -> %ld + %ld\n", address, page, offset);
		}
	}

	// Free all resources
	fclose(backingStore);
	fclose(addressList);

	return 0;
}

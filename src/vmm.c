/* Main file for Virtual Memory Mapper
 * Author: Michael Welborn
 * Date: 2014-11-08 */

#include <stdio.h>

int main(int argc, char** argv) {
	FILE* bstore;
	FILE* address;

	// Exit if insufficient arguments
	if (argc < 3) {
		fprintf(stderr, "vmm: Insufficient arguments\nUsage: vmm backing_store_file address_file\n");
		return 0;
	}

	// Open the files and exit on failure
 	if ((bstore = fopen(argv[1], "r")) == NULL) {
		fprintf(stderr, "vmm: %s: Cannot open backing store binary\n", argv[1]);
		return 0;
	}
 	if ((address = fopen(argv[2], "r")) == NULL) {
		fprintf(stderr, "vmm: %s: Cannot open address file", argv[2]);
		return 0;
	}

	// Do Stuff

	// Free all resources
	fclose(bstore);
	fclose(address);

	return 0;
}

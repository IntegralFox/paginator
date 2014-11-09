/* Option implementation */

#include <unistd.h>
#include "options.h"

unsigned int printHex = 0;

void parseOptions(int* argc, char*** argv) {
	int flag;
	while ((flag = getopt(*argc, *argv, "h")) != -1) {
		if (flag == 'h') {
			printHex = 1;
		}
	}
	*argc -= optind;
	*argv += optind;
}

/* Option implementation */

#include <unistd.h>
#include "options.h"

struct Options opt;

void parseOptions(int* argc, char*** argv) {
	// Set Defaults
	opt.printHex = 0;
	opt.frameSize = 256;
	opt.frameNum = 256;
	opt.pageNum = 256;

	// Parse any new options
	int flag;
	while ((flag = getopt(*argc, *argv, "h")) != -1) {
		if (flag == 'h') {
			opt.printHex = 1;
		}
	}
	*argc -= optind;
	*argv += optind;
}

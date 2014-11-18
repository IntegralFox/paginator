/* Option implementation */

#include <unistd.h>
#include <stdlib.h>
#include "options.h"

struct Options opt;

void parseOptions(int* argc, char*** argv) {
	// Set Defaults
	opt.printHex = 0;
	opt.frameSize = 256;
	opt.frameNum = 256;
	opt.offsetBits = 8;
	opt.offsetMask = (1 << opt.offsetBits) - 1;
	opt.pageNum = 256;
	opt.pageMask = ~opt.offsetMask;

	// Parse any new options
	int flag;
	while ((flag = getopt(*argc, *argv, "f:hp:")) != -1) {
		if (flag == '?') {
			*argc = 0;
		} else if (flag == 'h') {
			opt.printHex = 1;
		} else if (flag == 'f' ) {
			opt.frameNum = atol(optarg);
		} else if (flag == 'p') {
			opt.pageNum = atol(optarg);
		}
	}
	*argc -= optind;
	*argv += optind;
}

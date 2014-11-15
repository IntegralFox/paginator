/* Option implementation */

#include <unistd.h>
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
	opt.pageBits = 8;
	opt.pageMask = ~opt.offsetMask;

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

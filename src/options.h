/* Defines program wide options based on user supplied flags */

#ifndef VMM_OPTIONS
#define VMM_OPTIONS

struct Options {
	int printHex;
	int frameSize;
	int frameNum;
	unsigned long offsetMask;
	int offsetBits;
	int pageNum;
	unsigned long pageMask;
};

extern struct Options opt;

void parseOptions(int*, char***);

#endif

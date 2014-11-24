/* Defines program wide options based on user supplied flags */

#ifndef VMM_OPTIONS
#define VMM_OPTIONS

struct Options {
	int printHex;
	int debug;
	unsigned long frameSize;
	unsigned long frameNum;
	unsigned long offsetMask;
	unsigned long offsetBits;
	unsigned long pageNum;
	unsigned long pageMask;
};

extern struct Options opt;

void parseOptions(int*, char***);

#endif

/* Defines program wide options based on user supplied flags */

#ifndef VMM_OPTIONS
#define VMM_OPTIONS

struct Options {
	int printHex;
	int frameSize;
	int frameNum;
	int pageNum;
};

extern struct Options opt;

void parseOptions(int*, char***);

#endif

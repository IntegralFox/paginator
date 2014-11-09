/* Defines program wide options based on user supplied flags */

#ifndef VMM_OPTIONS
#define VMM_OPTIONS

unsigned int printHex = 0;

void parseOptions(int& argc, char** argv) {
	int flag;
	while ((flag = getopt(argc, argv, "h")) != -1) {
		if (flag == 'h') {
			printHex = 1;
		}
	}
	argc -= optind;
	argv += optind;
}

#endif

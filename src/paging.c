/* Implementation of page related activites */

#include "paging.h"
#include "options.h"

unsigned long pageOf(unsigned long address) {
	address = address & LOG_ADDR_MASK;
	address = address >> OFFSET_BITS;
	return address;
}

unsigned long offsetOf(unsigned long address) {
	address = address & OFFSET_MASK;
	return address;
}

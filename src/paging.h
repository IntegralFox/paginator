/* Header for page related activities */
#ifndef VMM_PAGING
#define VMM_PAGING

// 2^8 bytes in a frame -> 8 bits in address for offset
#define FRAME_SIZE 256
#define OFFSET_BITS 8
#define OFFSET_MASK ((1 << OFFSET_BITS) - 1)

// 2^8 pages -> 8 bits in address for page
#define NUM_PAGES 256
#define PAGE_BITS 8

// Logical address size
#define LOG_ADDR_SIZE (OFFSET_BITS + PAGE_BITS)
#define LOG_ADDR_MASK ((1 << LOG_ADDR_SIZE) - 1)

// Gets the page number from a logical address
unsigned long pageOf(unsigned long);

// Gets the offset from a logical address
unsigned long offsetOf(unsigned long);

#endif

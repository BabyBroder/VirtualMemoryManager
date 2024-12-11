#ifndef CONSTANT_H
#define CONSTANT_H

#define ADDRESS_SIZE 1000
#define BACKING_STORE_SIZE 65536

// Number of entries in the page table 2^8 entries in the page table
// 2^8 entries in the page table
#define PAGE_TABLE_ENTRIES 256

// Page size in bytes
// Page size of 2^8 bytes
#define PAGE_SIZE 256

// Number of entries in the TLB (Translation Lookaside Buffer)
// 16 entries in the TLB
#define TLB_ENTRIES 16

// Frame size in bytes
// Frame size of 2^8 bytes
#define FRAME_SIZE 256

// 256 frames
#define TOTAL_FRAMES 256

// Total physical memory size in bytes
// Physical memory of 65,536 bytes (256 frames × 256-byte frame size)
#define PHYSICAL_MEMORY_SIZE (TOTAL_FRAMES * FRAME_SIZE)

#endif // CONSTANT_H

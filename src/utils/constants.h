/**
 * @file constants.h
 * @brief This header file defines various constants used in the Virtual Memory Manager project.
 *
 * The constants defined in this file include sizes for addresses, backing store, page table entries,
 * page size, TLB entries, frame size, total frames, and physical memory size.
 *
 * @details
 * - ADDRESS_SIZE: Size of the address space.
 * - BACKING_STORE_SIZE: Size of the backing store.
 * - PAGE_TABLE_ENTRIES: Number of entries in the page table (2^8 entries).
 * - PAGE_SIZE: Size of a page in bytes (2^8 bytes).
 * - TLB_ENTRIES: Number of entries in the Translation Lookaside Buffer (TLB).
 * - FRAME_SIZE: Size of a frame in bytes (2^8 bytes).
 * - TOTAL_FRAMES: Total number of frames.
 * - PHYSICAL_MEMORY_SIZE: Total size of physical memory in bytes (256 frames × 256-byte frame size).
 */

#ifndef CONSTANT_H
#define CONSTANT_H


#define ADDRESS_SIZE 1000
#define BACKING_STORE_SIZE 65536

// Index for algorithm
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

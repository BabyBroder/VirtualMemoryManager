/**
 * @file constants.h
 * @brief This header file contains constants used in the Virtual Memory Manager.
 *
 * This file defines various constants such as sizes and limits for address space,
 * backing store, page table, TLB, frames, and physical memory.
 *
 * Constants:
 * - ADDRESS_SIZE: Size of the address space.
 * - BACKING_STORE_SIZE: Size of the backing store.
 * - OFFSET_BITS: Number of bits used for the offset.
 * - MAX_PAGE_NUMBER: Maximum value of the page number.
 * - PAGE_TABLE_ENTRIES: Number of entries in the page table.
 * - PAGE_SIZE: Size of a page in bytes.
 * - TLB_ENTRIES: Number of entries in the Translation Lookaside Buffer (TLB).
 * - FRAME_SIZE: Size of a frame in bytes.
 * - TOTAL_FRAMES: Total number of frames.
 * - PHYSICAL_MEMORY_SIZE: Total size of physical memory in bytes.
 */


#ifndef CONSTANT_H
#define CONSTANT_H

#ifdef TEST

#define ADDRESS_SIZE 30
#define BACKING_STORE_SIZE 256 * 30

#define OFFSET_BITS 8

// Max value of page_number
#define MAX_PAGE_NUMBER 255

// Number of entries in the page table (2^8)
#define PAGE_TABLE_ENTRIES 256

// Page size of 2^8 bytes
#define PAGE_SIZE 256

// Number of entries in the TLB (Translation Lookaside Buffer)
#define TLB_ENTRIES 16

// Frame size of 2^8 bytes
#define FRAME_SIZE 256

// 256 frames
#define TOTAL_FRAMES 10

// Total physical memory size in bytes
#define PHYSICAL_MEMORY_SIZE (TOTAL_FRAMES * FRAME_SIZE)

#else

#define ADDRESS_SIZE 1000
#define BACKING_STORE_SIZE 256 * 256

#define OFFSET_BITS 8

// Max value of page_number
#define MAX_PAGE_NUMBER 255

// Number of entries in the page table (2^8)
#define PAGE_TABLE_ENTRIES 256

// Page size of 2^8 bytes
#define PAGE_SIZE 256

// Number of entries in the TLB (Translation Lookaside Buffer)
#define TLB_ENTRIES 16

// Frame size of 2^8 bytes
#define FRAME_SIZE 256

// 256 frames
#define TOTAL_FRAMES 128

// Total physical memory size in bytes
#define PHYSICAL_MEMORY_SIZE (TOTAL_FRAMES * FRAME_SIZE)

#endif // TEST

#endif // CONSTANT_H

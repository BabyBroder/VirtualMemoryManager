#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "physical_memory.h"  // Use relative path
#include "utils/constants.h"
#include "algorithms/algorithm.h"
#include "virtual_memory.h"
#include "memory_manager.h"
#include "page_table.h"
#include "tlb.h"

struct PhysicalMemory;  
typedef struct PhysicalMemory PhysicalMemory;

/**
 * @brief Initializes the disk manager with the provided virtual memory, physical memory, TLB, page table, and algorithm.
 *
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param tlb Pointer to the TLB structure.
 * @param page_table Pointer to the PageTable structure.
 * @param algorithm The algorithm to be used for managing the disk.
 */
void initialize_disk_manager(VirtualMemory *virtual_memory, PhysicalMemory *physical_memory, TLB *tlb, PageTable *page_table, Algorithm algorithm);

/**
 * @brief Reads data from virtual memory into a frame.
 *
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param page_number The page number to read from.
 * @param offset The offset within the page to start reading.
 * @param size The number of bytes to read.
 * @param frame_data Pointer to the buffer where the frame data will be stored.
 */
void read_virutual_memory_to_frame(VirtualMemory *virtual_memory, uint8_t page_number, uint8_t offset, uint16_t size, char *frame_data);

#endif // DISK_MANAGER_H

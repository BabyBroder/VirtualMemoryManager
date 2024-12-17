/**
 * @file disk_manager.h
 * @brief Header file for managing physical memory in the virtual memory manager.
 */
#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include "../structure/structure.h"

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
void read_virutual_memory_to_frame(VirtualMemory *virtual_memory, int page_number, int offset, int size, char *frame_data);

#endif // DISK_MANAGER_H

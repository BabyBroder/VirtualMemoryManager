/**
 * @file disk_manager.h
 * @brief Header file for the Disk Manager module.
 *
 * This file contains the definitions and function declarations for managing
 * disk operations in the Virtual Memory Manager project.
 */
#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/constants.h"
#include "algorithms/algorithm.h"
#include "virtual_memory.h"
#include "physical_memory.h"
#include "memory_manager.h"
#include "page_table.h"
#include "tlb.h"


 /**
    * @brief Initializes the disk manager.
    *
    * This function sets up the disk manager with the provided virtual memory,
    * physical memory, TLB, page table, and page replacement algorithm.
    *
    * @param virtual_memory Pointer to the VirtualMemory structure.
    * @param physical_memory Pointer to the PhysicalMemory structure.
    * @param tlb Pointer to the TLB structure.
    * @param page_table Pointer to the PageTable structure.
    * @param algorithm The page replacement algorithm to be used.
    */
void initialize_disk_manager(VirtualMemory *virtual_memory, PhysicalMemory *physical_memory, TLB *tlb, PageTable *page_table, Algorithm algorithm);

 /**
    * @brief Swaps in a page from the disk to physical memory.
    *
    * This function handles the process of bringing a page from the disk into
    * physical memory when a page fault occurs. It updates the TLB and page table
    * accordingly.
    *
    * @param virtual_memory Pointer to the VirtualMemory structure.
    * @param physical_memory Pointer to the PhysicalMemory structure.
    * @param tlb Pointer to the TLB structure.
    * @param page_table Pointer to the PageTable structure.
    * @param virtual_address The virtual address of the page to be swapped in.
    */

void read_virutual_memory_to_frame(VirtualMemory *virtual_memory, uint8_t page_number, uint8_t offset, uint16_t size, char *frame_data);

#endif // DISK_MANAGER_H

/**
 * @file physical_memory.h
 * @brief Header file for managing physical memory in a virtual memory manager.
 *
 * This file contains the definitions and function prototypes for managing
 * physical memory, including initializing the memory, adding pages, reading
 * from and writing to memory, and finding free frames.
 */

#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <stdint.h>
#include <stdbool.h>
#include "utils/constants.h"
#include "algorithms/algorithm.h"

/**
 * @struct Frame
 * @brief Represents a single frame in physical memory.
 */
typedef struct
{
    char data[FRAME_SIZE]; /**< Data stored in the frame. */
} Frame;

/**
 * @struct PhysicalMemory
 * @brief Represents the physical memory.
 */
typedef struct
{
    Frame frames[TOTAL_FRAMES]; /**< Array of frames in physical memory. */
    int nums_frames; /**< Number of frames currently in use. */
    Algorithm algorithm; /**< Algorithm used for page replacement. */
    AlgorithmStruct algorithm_struct; /**< Data structure for the algorithm. */
} PhysicalMemory;

/**
 * @brief Initializes the physical memory.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param algorithm The algorithm to be used for page replacement.
 */
void initialize_physical_memory(PhysicalMemory *physical_memory, Algorithm algorithm);

/**
 * @brief Adds a page to the physical memory.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param page The page number to be added.
 * @param current_index The current index in the page table.
 */
void add_page_to_physical_memory(PhysicalMemory *physical_memory, int page, int current_index);

/**
 * @brief Reads data from the physical memory.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param physical_address The physical address to read from.
 * @param buffer Buffer to store the read data.
 * @param size Number of bytes to read.
 * @return Number of bytes read, or -1 on error.
 */
int read_from_physical_memory(PhysicalMemory *physical_memory, uint32_t physical_address, char *buffer, int size);

/**
 * @brief Writes data to the physical memory.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param physical_address The physical address to write to.
 * @param buffer Buffer containing the data to write.
 * @param size Number of bytes to write.
 * @return Number of bytes written, or -1 on error.
 */
int write_to_physical_memory(PhysicalMemory *physical_memory, uint32_t physical_address, const char *buffer, int size);

/**
 * @brief Finds a free frame in the physical memory.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param current_index The current index in the page table.
 * @return Index of the free frame, or -1 if no free frame is available.
 */
int find_free_frame(PhysicalMemory *physical_memory, int current_index);

#endif // PHYSICAL_MEMORY_H

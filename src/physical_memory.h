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
#include "virtual_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    uint16_t PhysicalAddress;
    char data;
} FrameData;

/**
 * @struct Frame
 * @brief Represents a single frame in physical memory.
 */
typedef struct
{   
    bool valid; /**< valid bits to tell frame is empty or not. */
    uint16_t frame_number; 
    uint16_t page_number;
    FrameData frame_data[256]; /**< Data stored in the frame. */
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
 * @brief Chooses an entry to replace in the Physical Memory.
 *
 * This function selects an entry in the Physical Memory to replace based on the
 * specified replacement algorithm.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param page_number The logical page number to add.
 * @param frame_number The physical frame number to add.
 * @param current_index The current index in the Physical Memory.
 * @return The index of the entry to replace.
 */
int find_entry_to_replace(PhysicalMemory *physical_memory, uint8_t page_number, uint8_t frame_number, int current_index);


/**
 * @brief Adds a page to the physical memory.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param page The page number to be added.
 * @param current_index The current index in the page table.
 */

void add_page_to_physical_memory(PhysicalMemory *physical_memory, uint8_t  frame_number, uint8_t  page_number, Frame *frame);

/**
 * @brief Reads data from the physical memory.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param physical_address The physical address to read from.
 * @param buffer Buffer to store the read data.
 * @param size Number of bytes to read.
 * @return Number of bytes read, or -1 on error.
 */

char* read_from_physical_memory(PhysicalMemory *physical_memory, uint8_t  frame_number, uint8_t  offset);
#endif // PHYSICAL_MEMORY_H;

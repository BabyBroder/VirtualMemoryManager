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

#include "../algorithms/algorithms.h"

/**
 * @struct Frame
 * @brief Represents a single frame in physical memory.
 */
typedef struct
{
    bool valid; /**< valid bits to tell frame is empty or not. */
    uint16_t page_number;
    char frame_data[256]; /**< Data stored in the frame. */
} Frame;

/**
 * @struct PhysicalMemory
 * @brief Represents the physical memory.
 */
typedef struct 
{
    Frame frames[TOTAL_FRAMES];
    int nums_frames;
    Algorithm algorithm;
    AlgorithmStruct algorithm_struct;
    bool initialized;
} PhysicalMemory;

/**
 * @brief Initializes the physical memory.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param algorithm The algorithm to be used for page replacement.
 */
void initialize_physical_memory(PhysicalMemory *physical_memory, Algorithm algorithm);


/**
 * @brief Finds a free frame in the Physical Memory.
 *
 * This function searches for a free frame in the Physical Memory.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @return The index of the free frame, or -1 if no free frame is found.
 */
int find_free_frame(PhysicalMemory *physical_memory);


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
 * This function adds a page to the physical memory at the specified frame number.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param frame_number The frame number to add the page to.
 * @param page_number The page number to add.
 */
uint8_t add_page_to_physical_memory(PhysicalMemory *physical_memory, VirtualMemory *virtual_memory, uint8_t frame_number, uint8_t page_number);

/**
 * @brief Reads data from physical memory.
 *
 * This function reads data from the physical memory at the specified frame number and offset.
 *
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param frame_number The frame number to read from.
 * @param offset The offset within the frame to start reading.
 * @return The data read from the physical memory.
 */
char *read_from_physical_memory(PhysicalMemory *physical_memory, uint8_t frame_number, uint8_t offset);

#endif // PHYSICAL_MEMORY_H;

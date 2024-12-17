/**
 * @file virtual_memory.h
 * @brief Header file for the Virtual Memory Manager project.
 *
 * This file contains the necessary includes and definitions for the
 * Virtual Memory Manager project.
 */

#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

/**
 * @struct VirtualMemory
 * @brief Represents the virtual memory.
 *
 * @var VirtualMemory::data
 * Data array representing the backing store.
 *
 * @var VirtualMemory::address
 * Array of pointers representing addresses.
 *
 * @var VirtualMemory::initialized
 * Flag indicating if the virtual memory has been initialized.
 */
typedef struct VirtualMemory
{
    char *data;       /**< Data array representing the backing store. */
    int *address;     /**< Array of pointers representing addresses. */
    bool initialized; /**< Flag indicating if the virtual memory has been initialized. */
} VirtualMemory;

/**
 * @brief Initializes the virtual memory with the provided address and backing store files.
 *
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param address_file The address file to read from.
 * @param backing_store_file The backing store file to read from.
 */
void initialize_virtual_memory(VirtualMemory *virtual_memory, char *address_file, char *backing_store_file);

/**
 * @brief Reads data from the virtual memory.
 *
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param page_number The page number to read from.
 * @param offset The offset within the page to start reading.
 * @param size The number of bytes to read.
 * @return A pointer to the data read from the virtual memory.
 */
char *readVirtualMemory(VirtualMemory *virtual_memory, int page_number, int offset, int size);

/**
 * @brief Frees the virtual memory.
 *
 * @param virtual_memory Pointer to the VirtualMemory structure.
 */
void free_virtual_memory(VirtualMemory *virtual_memory);

#endif // VIRTUAL_MEMORY_H

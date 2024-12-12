/**
 * @file virtual_memory.h
 * @brief Header file for the Virtual Memory Manager project.
 *
 * This file contains the necessary includes and definitions for the
 * Virtual Memory Manager project.
 */

#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "utils/constants.h"
#include "utils/parser.h"

/**
 * @brief Structure representing the virtual memory.
 */
typedef struct {
    char *data; /**< Data array representing the backing store. */
    int *address;    /**< Array of pointers representing addresses. */
    bool initialized; /**< Flag indicating if the virtual memory has been initialized. */   
} VirtualMemory;

/**
 * @brief Initializes the virtual memory.
 * 
 * @param virtual_memory Pointer to the VirtualMemory structure to be initialized.
 * @param address_file Path to the file containing address information.
 * @param backing_store_file Path to the file containing backing store data.
 */
void initialize_virtual_memory(VirtualMemory *virtual_memory, char* address_file, char* backing_store_file);

/**
 * @brief Reads a byte from the virtual memory.
 * 
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param virtual_address The virtual address to read from.
 * @return Pointer to the byte read from the backing store.
 */
char *read_BACKINGSTORE(VirtualMemory *virtual_memory, uint32_t virtual_address);

#endif // VIRTUAL_MEMORY_H
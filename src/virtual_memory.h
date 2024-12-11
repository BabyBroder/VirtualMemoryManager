#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <fcntl.h>
#include "utils/constants.h"

typedef struct{
    char data[BACKING_STORE_SIZE];
    int *address[ADDRESS_SIZE];
} VirtualMemory;

// Initializes the virtual memory
void initialize_virtual_memory(VirtualMemory *virtual_memory, char* address_file, char* backing_store_file);

// Reads  byte from the virtual memory
char *read_BACKINGSTORE(VirtualMemory *virtual_memory, uint32_t virtual_address);
#endif // VIRTUAL_MEMORY_H
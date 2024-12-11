#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <stdint.h>
#include <stdbool.h>
#include "utils/constants.h"

typedef struct{
    char data[FRAME_SIZE];
} Frame;

typedef struct {
    Frame *frames;
    int frame_count;
} PhysicalMemory;

void initialize_physical_memory(PhysicalMemory *physical_memory);

int read_from_physical_memory(PhysicalMemory *physical_memory, uint32_t physical_address, char *buffer, int size);

int write_to_physical_memory(PhysicalMemory *physical_memory, uint32_t physical_address, const char *buffer, int size);

#endif // PHYSICAL_MEMORY_H

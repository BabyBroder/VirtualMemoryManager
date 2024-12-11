#ifndef PHYSICAL_MEMORY_H
#define PHYSICAL_MEMORY_H

#include <stdint.h>
#include <stdbool.h>
#include "utils/constants.h"
#include "algorithms/algorithm.h"

typedef struct{
    char data[FRAME_SIZE];
} Frame;

typedef struct {
    Frame frames[TOTAL_FRAMES];
    int nums_frames;
} PhysicalMemory;


void initialize_physical_memory(PhysicalMemory *physical_memory);

int read_from_physical_memory(PhysicalMemory *physical_memory, uint32_t physical_address, char *buffer, int size);

int write_to_physical_memory(PhysicalMemory *physical_memory, uint32_t physical_address, const char *buffer, int size);

int find_free_frame(PhysicalMemory *physical_memory, Algorithm algorithm);

#endif // PHYSICAL_MEMORY_H

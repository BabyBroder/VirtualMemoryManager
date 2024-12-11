#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "physical_memory.h"
#include "utils/constants.h"

void initialize_physical_memory(PhysicalMemory *physical_memory){}

int read_from_physical_memory(PhysicalMemory *physical_memory, uint32_t physical_address, char *buffer, int size){}

int write_to_physical_memory(PhysicalMemory *physical_memory, uint32_t physical_address, const char *buffer, int size){}

int find_free_frame(){}

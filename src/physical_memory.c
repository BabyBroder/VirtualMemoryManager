#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "physical_memory.h"
#include "utils/constants.h"
#include <stdint.h>

void initialize_physical_memory(PhysicalMemory *physical_memory){
    physical_memory->nums_frames = TOTAL_FRAMES;
    for(int i = 0; i < TOTAL_FRAMES; i++){
        memset(physical_memory->frames[i].data, 0, FRAME_SIZE);
    }
}

int read_from_physical_memory(PhysicalMemory *physical_memory, uint32_t physical_address, char *buffer, int size){
    uint32_t frame_number = physical_address / FRAME_SIZE;
    uint32_t offset = physical_address % FRAME_SIZE;
    if(frame_number >= physical_memory->nums_frames){
        return -1;
    }
    if(offset + size > FRAME_SIZE){
        return -1;
    }
    memcpy(buffer, physical_memory->frames[frame_number].data + offset, size);
    return size;
}

int write_to_physical_memory(PhysicalMemory *physical_memory, uint32_t physical_address, const char *buffer, int size){
    uint32_t frame_number = physical_address / FRAME_SIZE;
    uint32_t offset = physical_address % FRAME_SIZE;
    if(frame_number >= physical_memory->nums_frames){
        return -1;
    }
    if(offset + size > FRAME_SIZE){
        return -1;
    }
    memcpy(physical_memory->frames[frame_number].data + offset, buffer, size);
    return size;
}


int find_free_frame(PhysicalMemory *physical_memory){
    for(int i = 0; i < TOTAL_FRAMES; i++){
        if(physical_memory->frames[i].data == NULL){
            return i;
        }
    }

    // Page replacement algorithm
    
}

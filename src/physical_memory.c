#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "physical_memory.h"
#include "utils/constants.h"
#include <stdint.h>

void initialize_physical_memory(PhysicalMemory *physical_memory, Algorithm algorithm){
    physical_memory->nums_frames = TOTAL_FRAMES;
    for(int i = 0; i < TOTAL_FRAMES; i++){
        memset(physical_memory->frames[i].data, 0, FRAME_SIZE);
    }
    physical_memory->algorithm = algorithm;
    if( algorithm == FIFO){
        initialize_fifo(&physical_memory->algorithm_struct.fifo, TOTAL_FRAMES);
    } else if( algorithm == LRU){
        initialize_lru(&physical_memory->algorithm_struct.lru, TOTAL_FRAMES);
    } else if( algorithm == OPT){
        initialize_optimal(&physical_memory->algorithm_struct.optimal, TOTAL_FRAMES);
    }
}

void add_page_to_physical_memory(PhysicalMemory *physical_memory, int page, int current_index){
    int free_frame = find_free_frame(physical_memory, current_index);
    if(physical_memory->algorithm == FIFO){
        fifo_add_page(&physical_memory->algorithm_struct.fifo, page);
    } else if(physical_memory->algorithm == LRU){
        lru_add_page(&physical_memory->algorithm_struct.lru, page);
    } else if(physical_memory->algorithm == OPT){
        optimal_add_page(&physical_memory->algorithm_struct.optimal, page);
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


int find_free_frame(PhysicalMemory *physical_memory, int current_index){
    for(int i = 0; i < TOTAL_FRAMES; i++){
        if(physical_memory->frames[i].data == NULL){
            return i;
        }
    }

    // Page replacement algorithm
    if( physical_memory->algorithm == FIFO){
        return fifo_choose_page_to_replace(physical_memory);
    } else if( physical_memory->algorithm  == LRU){
        return lru_choose_page_to_replace(physical_memory);
    } else if( physical_memory->algorithm  == OPT){
        return optimal_choose_page_to_replace(physical_memory, current_index);
    }
}

#include "../../lib/memory/memory.h"

void initialize_physical_memory(PhysicalMemory *physical_memory, Algorithm algorithm)
{
    // if (physical_memory->initialized)
    // {
    //     printf("Physical memory already initialized\n");
    //     exit(EXIT_FAILURE);
    // }

    // physical_memory = (PhysicalMemory *)malloc(sizeof(PhysicalMemory));
    if (physical_memory == NULL)
    {
        printf("Failed to allocate memory for physical memory\n");
        exit(EXIT_FAILURE);
    }

    physical_memory->nums_frames = 0;
    physical_memory->algorithm = algorithm;

    if (algorithm == FIFO_ALGORITHM)
        initialize_fifo(&physical_memory->algorithm_struct.fifo, TOTAL_FRAMES);

    else if (algorithm == LRU_ALGORITHM)
        initialize_lru(&physical_memory->algorithm_struct.lru, TOTAL_FRAMES);
    else
    {
        printf("Invalid algorithm\n");
        exit(EXIT_FAILURE);
    }
}

int find_free_frame(PhysicalMemory *physical_memory)
{
    for (int i = 0; i < FRAME_SIZE; i++)
    {
        if (!physical_memory->frames[i].valid)
        {
            return i;
        }
    }
    return -1;
}

int find_entry_to_replace(PhysicalMemory *physical_memory, uint8_t page_number, uint8_t frame_number, int current_index)
{
    // find suitable entry
    int needReplace = -2;
    if (physical_memory->algorithm == FIFO_ALGORITHM)
    {
        needReplace = fifo_add_page(&physical_memory->algorithm_struct.fifo, page_number);
    }
    else if (physical_memory->algorithm == LRU_ALGORITHM)
    {
        needReplace = lru_add_page(&physical_memory->algorithm_struct.lru, page_number);
    }
    else if (physical_memory->algorithm == OPT_ALGORITHM)
    {
        needReplace = optimal_add_page(&physical_memory->algorithm_struct.optimal, page_number, current_index);
    }
    return needReplace;
}

uint8_t add_page_to_physical_memory(PhysicalMemory *physical_memory, VirtualMemory *virtual_memory, uint8_t frame_number, uint8_t page_number)
{
    if (physical_memory == NULL)
    {
        printf("Physical memory not initialized\n");
        exit(EXIT_FAILURE);
    }

    int goodState = -1;
    goodState = find_entry_to_replace(physical_memory, page_number, frame_number, -1);

    if (goodState == -1)
    {
        // finding free frame to add page
        for (int i = 0; i < FRAME_SIZE; i++)
        {
            if (!physical_memory->frames[i].valid)
            {
                physical_memory->frames[i].valid = true;
                physical_memory->frames[i].page_number = page_number;
                //printf("Page %d added to frame %d\n", page_number, i);
                char *framedata = readVirtualMemory(virtual_memory, page_number, 0, FRAME_SIZE);
                memcpy(physical_memory->frames[i].frame_data, framedata, FRAME_SIZE);
                physical_memory->nums_frames++;
                free(framedata);
                return physical_memory->nums_frames - 1;
            }
        }
    }

    // indx = frame number exist in physical memory or need to replace
    int indx = goodState;
    if (indx >= TLB_ENTRIES)
    { // wrong index
        printf("Error index replacement\n");
        exit(EXIT_FAILURE);
        return -1;
    }
    physical_memory->frames[indx].page_number = page_number;
    return indx;
}

char *read_from_physical_memory(PhysicalMemory *physical_memory, uint8_t frame_number, uint8_t offset)
{

    if (physical_memory->frames[frame_number].valid)
        return &physical_memory->frames[frame_number].frame_data[offset];
    else
        return NULL;
}
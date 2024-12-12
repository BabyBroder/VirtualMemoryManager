#include "physical_memory.h"


void initialize_physical_memory(PhysicalMemory *physical_memory, Algorithm algorithm)
{
    if(physical_memory != NULL)
    {
        printf("Physical memory already initialized\n");
        exit(EXIT_FAILURE);
    }

    physical_memory = (PhysicalMemory *)malloc(sizeof(PhysicalMemory));
    if(physical_memory == NULL)
    {
        printf("Failed to allocate memory for physical memory\n");
        exit(EXIT_FAILURE);
    }

    physical_memory->nums_frames = 0;
    physical_memory->algorithm = algorithm;
    if(algorithm == FIFO_ALGORITHM)
    {
        initialize_fifo(&physical_memory->algorithm_struct.fifo, TOTAL_FRAMES);
    }
    else if(algorithm == LRU_ALGORITHM)
    {
        initialize_lru(&physical_memory->algorithm_struct.lru, TOTAL_FRAMES);
    }else{
        printf("Invalid algorithm\n");
        exit(EXIT_FAILURE);
    }
}

void add_page_to_physical_memory(PhysicalMemory *physical_memory, int frame_number, Frame *frame)
{
    if(physical_memory == NULL)
    {
        printf("Physical memory not initialized\n");
        exit(EXIT_FAILURE);
    }

    // if(physical_memory->nums_frames == TOTAL_FRAMES)
    // {
    //     printf("Physical memory is full\n");
    //     exit(EXIT_FAILURE);
    // }

    // physical_memory->frames[frame_number] = *frame;
    // physical_memory->nums_frames++;
    int goodState = -1;
    goodState = find_entry_to_replacment(physical_memory, frame_number, frame, frame_number);
}

// void tlb_add_entry(TLB *tlb, uint16_t page_number, uint16_t frame_number, int current_index)
// {
//     int goodState = -1;
//     // finding free TLB entry to add
//     goodState = find_entry_to_replacment(tlb, page_number, frame_number, current_index);
//     if (goodState < 0)
//     {
//         if (goodState == -1)
//             for (int i = 0; i < TLB_ENTRIES; i++)
//             {
//                 if (!tlb->entries[i].valid)
//                 {
//                     tlb->entries[i].valid = true;
//                     tlb->entries[i].frame_number = frame_number;
//                     tlb->entries[i].page_number = page_number;
//                     return;
//                 }
//             }
//         else
//             return;
//     }
//     // TLB is full use page replacement
//     // choose a page to be replaced by using tlb algorithm
//     int indx = goodState;
//     if (indx >= TLB_ENTRIES)
//     { // wrong index
//         printf("Error index replacement\n");
//         return;
//     }
//     tlb->entries[indx].frame_number = frame_number;
//     tlb->entries[indx].page_number = page_number;
// }
#include "../../lib/structure/structure.h"

void initialize_tlb(TLB *tlb, VirtualMemory *virtual_memory, Algorithm algorithm)
{
    // chossing algorithm
    tlb->algorithm = algorithm;
    if (algorithm == FIFO_ALGORITHM)
    {
        initialize_fifo(&tlb->algorithm_struct.fifo, TLB_ENTRIES);
    }
    else if (algorithm == LRU_ALGORITHM)
    {
        initialize_lru(&tlb->algorithm_struct.lru, TLB_ENTRIES);
    }
    else if (algorithm == OPT_ALGORITHM)
    {
        char *file_addresses = {"../../data/addresses.txt"};
        initialize_optimal(&tlb->algorithm_struct.optimal, file_addresses, TLB_ENTRIES);
    }
    // default value: invalid
    for (int i = 0; i < TLB_ENTRIES; i++)
    {
        tlb->entries[i].valid = false;
    }
}

int choose_entry_to_replace(TLB *tlb, uint16_t page_number, uint16_t frame_number, int current_index)
{
    // adding entry
    int needReplace = -2;
    if (tlb->algorithm == FIFO_ALGORITHM)
    {
        needReplace = fifo_add_page(&tlb->algorithm_struct.fifo, page_number);
    }
    else if (tlb->algorithm == LRU_ALGORITHM)
    {
        needReplace = lru_add_page(&tlb->algorithm_struct.lru, page_number);
    }
    else if (tlb->algorithm == OPT_ALGORITHM)
    {
        needReplace = optimal_add_page(&tlb->algorithm_struct.optimal, page_number, current_index);
    }
    return needReplace;
}

void tlb_add_entry(TLB *tlb, uint16_t page_number, uint16_t frame_number, int current_index)
{
    int goodState = -1;
    // finding free TLB entry to add
    goodState = choose_entry_to_replace(tlb, page_number, frame_number, current_index);
    if (goodState < 0)
    {
        if (goodState == -1)
            for (int i = 0; i < TLB_ENTRIES; i++)
            {
                if (!tlb->entries[i].valid)
                {
                    tlb->entries[i].valid = true;
                    tlb->entries[i].frame_number = frame_number;
                    tlb->entries[i].page_number = page_number;
                    return;
                }
            }
        else
            return;
    }
    // TLB is full use page replacement
    // choose a page to be replaced by using tlb algorithm
    int indx = goodState;
    if (indx >= TLB_ENTRIES)
    { // wrong index
        printf("Error index replacement\n");
        return;
    }
    tlb->entries[indx].frame_number = frame_number;
    tlb->entries[indx].page_number = page_number;
}

int tlb_lookup(TLB *tlb, uint16_t page_number)
{
    for (int i = 0; i < TLB_ENTRIES; i++)
    {
        // finding the TLB entry valid and match page number
        if (tlb->entries[i].valid &&
            tlb->entries[i].page_number == page_number)
            // TLB hit
            return tlb->entries[i].frame_number;
    }
    // TLB misssed
    return -1;
}

void print_tlb(const TLB *tlb)
{
    // print tlb
    printf("Page number - Frame number\n");
    for (int i = 0; i < TLB_ENTRIES; i++)
    {
        if (tlb->entries[i].valid)
        {
            int page_number = tlb->entries[i].page_number;
            int frame_number = tlb->entries[i].frame_number;
            printf("%d  %d\n", page_number, frame_number);
        }
    }
}
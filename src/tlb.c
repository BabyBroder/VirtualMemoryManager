#include <stdio.h>
#include <stdlib.h>
#include "tlb.h"
#include "page_table.h"
#include "utils/constants.h"
#include "fifo.h"
#include "lru.h"
#include "optimal.h"

void initialize_tlb(TLB *tlb, int replacement) {
    tlb->next_replace_index = replacement; // chossing algorithm 
    for(int i = 0 ;i < TLB_SIZE ;i++)
    {
        tlb->entries[i].valid = false;
    }
    if(tlb->next_replace_index == FIFO)
    {
        
    }
    else if(tlb->next_replace_index == OPT)
    {

    }
    else if(tlb->next_replace_index == LRU)
    {
        
    }
}

void tlb_add_entry(TLB *tlb, uint16_t page_number, uint16_t frame_number) {
    bool hasSpace = false;
    // finding free TLB entry to add
    for(int i = 0 ;i < TLB_SIZE ;i++)
    {
        if(!tlb->entries[i].valid)
        {
            tlb->entries[i].valid = true;
            tlb->entries[i].frame_number = frame_number;
            tlb->entries[i].page_number = page_number; 
            hasSpace = true;
            return;
        }
    }
    // TLB is full use page replacement
    if ( !hasSpace ) 
    {   // update later for algorithm
        // temporarily use first match
        tlb->entries[0].frame_number = frame_number;
        tlb->entries[0].page_number = page_number;
    }   
}

int tlb_lookup(TLB *tlb, uint16_t page_number) {
    for(int i = 0 ;i < TLB_SIZE ;i++)
    {
        // finding the TLB entry valid and match page number
        if(tlb->entries[i].valid&&
            tlb->entries[i].page_number == page_number)
                // TLB hit
                return tlb->entries[i].frame_number;
    }
    // TLB misssed
    return -1;
}

void print_tlb(const TLB *tlb) {
    printf("Page number - Frame number\n");
    for(int i = 0 ;i < TLB_SIZE ;i++)
    {
        if(tlb->entries[i].valid){
            int page_number = tlb->entries[i].page_number;
            int frame_number = tlb->entries[i].frame_number; 
            printf("%d  %d\n",page_number,frame_number);
        }
    }
}

#include "../../lib/structure/structure.h"

/**
 * @brief Initializes the TLB with the specified virtual memory and replacement algorithm.
 *
 * This function initializes the TLB with the specified virtual memory and
 * replacement algorithm. The TLB is initialized with all entries marked as
 * invalid.
 *
 * @param tlb Pointer to the TLB structure.
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param algorithm The replacement algorithm to use.
 */
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
        initialize_optimal(&tlb->algorithm_struct.optimal, virtual_memory, TLB_ENTRIES);
    }
    // default value: invalid
    for (int i = 0; i < TLB_ENTRIES; i++)
    {
        tlb->entries[i].valid = false;
    }
}

/**
 * @brief Chooses an entry to replace in the TLB.
 *
 * This function selects an entry in the TLB to replace based on the
 * specified replacement algorithm.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_number The logical page number to replace.
 * @param frame_number The physical frame number to replace.
 * @param current_index The current index in the TLB.
 * @return The index of the entry to replace.
 */
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

/**
 * @brief Adds an entry to the TLB.
 *
 * This function adds an entry to the TLB at the specified index.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_number The logical page number to add.
 * @param frame_number The physical frame number to add.
 * @param current_index The current index in the TLB.
 */
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

/**
 * @brief Looks up the TLB for a given page number.
 *
 * This function looks up the TLB for a given page number and returns the
 * corresponding frame number if the entry is valid.
 *
 * @param tlb Pointer to the TLB structure.
 * @param page_number The page number to look up.
 * @return The frame number corresponding to the page number, or -1 if the entry is not valid.
 */
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

/**
 * @brief Prints the contents of the TLB.
 *
 * This function prints the contents of the TLB to the console.
 *
 * @param tlb Pointer to the TLB structure.
 */
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

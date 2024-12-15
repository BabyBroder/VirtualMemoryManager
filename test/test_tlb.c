#include "../lib/structure/tlb.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    uint16_t page_number;
    uint16_t frame_number;
} TLB_input;

int main()
{
    TLB_input test[18];
    test[0].page_number = 10;
    test[0].frame_number = 9;

    for (uint16_t i = 1; i < 18; i++)
    {
        test[i].page_number = i;
        test[i].frame_number = i;
    }

    test[17].page_number = 10;
    test[17].frame_number = 9;
    // Allocate memory for the TLB
    TLB *_TLB = (TLB *)malloc(sizeof(TLB));
    if (_TLB == NULL)
    {
        printf("Error: Memory allocation for TLB failed!\n");
        return 1;
    }
    // Allocate memory for the Virtual Memory
    VirtualMemory *_VM = (VirtualMemory *)malloc(sizeof(VirtualMemory));
    if (_VM == NULL)
    {
        printf("Error: Memory allocation for Virtual Memory failed!\n");
        return 1;
    }

    initialize_virtual_memory(_VM, "addresses.txt", "BAKING_STORE.BIN");
    initialize_tlb(_TLB, _VM, LRU_ALGORITHM);
    for (int i = 0; i < 17; i++)
    {
        tlb_add_entry(
            _TLB,
            test[i].page_number,
            test[i].frame_number,
            i);
    }
    print_tlb(_TLB);
    printf("Page number: %d\nFrame number: %d\n", test[17].page_number, test[17].frame_number);
    tlb_add_entry(_TLB, test[17].page_number, test[17].frame_number, 17);

    print_tlb(_TLB);

    printf("Page number: %d\nFrame number: %d\n",
            test[13].page_number, test[13].frame_number);

    tlb_add_entry( _TLB, test[13].page_number, test[13].frame_number, 18);
    print_tlb(_TLB);
    
    printf("Page number: %d\nFrame number: %d\n",
            18, 18);

    tlb_add_entry(_TLB, 18, 18, 18);
    print_tlb(_TLB);
}
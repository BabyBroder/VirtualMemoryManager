#include "structure/tlb.h"
typedef struct
{
    int page_number;
    int frame_number;
} TLB_input;

int main()
{
    TLB_input test[18];
    test[0].page_number = 10;
    test[0].frame_number = 10;

    for (int i = 1; i < 18; i++)
    {
        test[i].page_number = i;
        test[i].frame_number = i;
    }

    test[17].page_number = 10;
    test[17].frame_number = 10;
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
    initialize_tlb(_TLB, _VM, FIFO_ALGORITHM);
    for (int i = 0; i < 17; i++)
    {
        add_entry_to_tlb(
            _TLB,
            test[i].page_number,
            test[i].frame_number,
            i);
    }
    print_tlb(_TLB);
    printf("Page number: %d\nFrame number: %d\n", test[17].page_number, test[17].frame_number);
    add_entry_to_tlb(_TLB, test[17].page_number, test[17].frame_number, 17);

    print_tlb(_TLB);

    printf("Page number: %d\nFrame number: %d\n",
            19, 19);

    add_entry_to_tlb( _TLB, 19, 19, 19);
    print_tlb(_TLB);
    
    printf("Page number: %d\nFrame number: %d\n",
            18, 18);

    add_entry_to_tlb(_TLB, 18, 18, 18);
    print_tlb(_TLB);
}
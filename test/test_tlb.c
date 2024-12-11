#include "../src/tlb.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct{
    uint16_t page_number;
    uint16_t frame_number;
}TLB_input;
int main()
{
    TLB_input test[18];
    for (uint16_t i = 0; i < 18; i++)
    {
        test[i].page_number = i;
        test[i].frame_number = i;
    }
     // Allocate memory for the TLB
    TLB *_TLB = (TLB *)malloc(sizeof(TLB));
    if (_TLB == NULL) {
        printf("Error: Memory allocation for TLB failed!\n");
        return 1;
    }
    initialize_tlb(_TLB, LRU_ALGORITHM);
    for (int i = 0; i < 17; i++)
    {
        tlb_add_entry(
            _TLB,
            test[i].page_number,
            test[i].frame_number,
            i
        );
    }
    print_tlb(_TLB);
    printf("%d\n",choose_entry_to_replace(_TLB,
            test[17].page_number,
            test[17].frame_number,
            17));
    tlb_add_entry(
            _TLB,
            test[17].page_number,
            test[17].frame_number,
            17
        );
    print_tlb(_TLB);
}
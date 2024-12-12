#include "../src/page_table.h"
#include "../src/disk_manager.h"
#include "../src/physical_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    PageTable* pageTable = (PageTable*) malloc(sizeof(PageTable));
    // initialize_page_table(pageTable);
    // link_page_table_to_frame(pageTable, 10, 20);
    // printf("Page[10] = %d\n", page_table_lookup(pageTable, 10));
    // printf("Page[11] = %d\n", page_table_lookup(pageTable, 11));
    // free_page_table(pageTable);
    return 0;
}
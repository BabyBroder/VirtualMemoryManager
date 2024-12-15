#include "../lib/structure/page_table.h"

int main()
{
    PageTable *page_table;
    initialize_page_table(page_table);
    
    link_page_table_to_frame(page_table, 1, 2);
    link_page_table_to_frame(page_table, 2, 3);

    printf("Page table lookup for page 1: %d\n", page_table_lookup(page_table, 1));
    printf("Page table lookup for page 2: %d\n", page_table_lookup(page_table, 2));

    free(page_table);
}
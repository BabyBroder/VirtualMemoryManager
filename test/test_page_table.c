#include "structure/page_table.h"

int main()
{
    PageTable *page_table;
    page_table = (PageTable *)malloc(sizeof(PageTable));
    if (page_table == NULL)
    {
        perror("Error allocating memory");
        exit(1);
    }
    initialize_page_table(page_table);

    link_page_table_to_frame(page_table, 1, 2);
    link_page_table_to_frame(page_table, 2, 3);
    link_page_table_to_frame(page_table, 3, 6);
    link_page_table_to_frame(page_table, 4, 12);
    link_page_table_to_frame(page_table, 5, 9);
    link_page_table_to_frame(page_table, 6, 30);
    link_page_table_to_frame(page_table, 7, 75);
    link_page_table_to_frame(page_table, 8, 4);
    link_page_table_to_frame(page_table, 9, 99);
    link_page_table_to_frame(page_table, 10, 2);
    link_page_table_to_frame(page_table, 11, 3);
    link_page_table_to_frame(page_table, 12, 6);
    link_page_table_to_frame(page_table, 13, 12);
    link_page_table_to_frame(page_table, 14, 9);
    link_page_table_to_frame(page_table, 15, 30);
    link_page_table_to_frame(page_table, 3, 75);
    link_page_table_to_frame(page_table, 6, 4);
    link_page_table_to_frame(page_table, 9, 99);

    // print page_table
    for (int i = 0; i < PAGE_TABLE_ENTRIES; i++)
    {
        printf("|Page number: %d | Frame number: %d|\n", i, page_table->entries[i].frame_number);
    }

    printf("Page table lookup for page 1: %d\n", page_table_lookup(page_table, 12));
    printf("Page table lookup for page 2: %d\n", page_table_lookup(page_table, 9));

    free(page_table);
}
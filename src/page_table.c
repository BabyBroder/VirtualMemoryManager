#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_table.h"

typedef struct {
    int page_id;
    int frame_id;
    int valid; //  0 invalid, 1 valid
} PageTableEntry;

PageTableEntry *page_table = NULL;
int page_table_size = 0;
Page *frames = NULL;
int frame_count = 0;

void initialize_page_table(int size) {
    page_table_size = size;
    page_table = (PageTableEntry *)malloc(size * sizeof(PageTableEntry));
    frames = (Page *)malloc(size * sizeof(Page));
    frame_count = size;
    for(int i = 0 ; i<size ;i++)
    {
        page_table[i].page_id = i;
        page_table[i].frame_id = -1; // chưa được map
        page_table[i].valid = 0;
        memset(frames[i].data, 0, sizeof(frames[i].data));
    }
}

int translate_address(int virtual_address) {
    int page_id = (virtual_address*page_table_size) + offset;
}

void update_page_table(int page_id, int frame_id) {}

Page *get_page(int page_id) {}

void load_page(int page_id, const char *data) {}

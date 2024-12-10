#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_table.h"
const int offset = 0; // vi tri co so cua vung nho ao la 0
typedef struct {
    int page_id;
    int frame_id;
    int valid; //  0 invalid, 1 valid
} PageTableEntry;

PageTableEntry *page_table = NULL;
int page_table_size = 256;
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
        frames[i].data="";
    }
}

int translate_address(int virtual_address) {
    int page_id = (((virtual_address-offset)>>8) & 0xFF)/page_table_size;
    int page_offset = (virtual_address-offset) & 0xFF;
    if(page_id>=page_table_size||!page_table[page_id].valid){
        printf("Error: Invalid virtual address or page not loaded!\n");
        return -1;
    }
    int frame_id = page_table[page_id].frame_id;
    int physical_address = (frame_id*page_table_size)+page_offset;
    return physical_address;
}

void update_page_table(int page_id, int frame_id) {
    if (page_id < 0 || page_id >= page_table_size) {
        printf("Error: Invalid page ID!\n");
        return;
    }
    page_table[page_id].frame_id = frame_id; // tu page map sang frame
    page_table[page_id].valid = 1;
}

Page *get_page(int page_id) {
    if (page_id < 0 || page_id >= page_table_size) {
        printf("Error: Invalid page ID!\n");
        return NULL;
    }

    if (!page_table[page_id].valid) {
        printf("Error: Page is not valid!\n");
        return NULL;
    }

    return &frames[page_table[page_id].frame_id];
}

void load_page(int page_id, const char *data) {
    if (page_id < 0 || page_id >= page_table_size) {
        printf("Error: Invalid page ID.\n");
        return;
    }
    int frame_id = page_id;  // khi memory cua logical va physical nhu nhau
    update_page_table(page_id,frame_id);
    frames[frame_id].data = data;
}

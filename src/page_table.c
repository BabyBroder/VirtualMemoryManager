#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "page_table.h"

typedef struct {
    int page_id;
    int frame_id;
    int valid; // 1 if the page is in memory, 0 otherwise
} PageTableEntry;

static PageTableEntry *page_table = NULL;
static int page_table_size = 0;
static Page *pages = NULL;

void initialize_page_table(int size) {}

int translate_address(int virtual_address) {}

void update_page_table(int page_id, int frame_id) {}

Page *get_page(int page_id) {}

void load_page(int page_id, const char *data) {}

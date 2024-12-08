#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk_manager.h"

#define MAX_DISK_PAGES 100

typedef struct {
    int id;
    char data[256];
} DiskPage;

static DiskPage disk[MAX_DISK_PAGES];
static int disk_size = 0;

void initialize_disk() {}

void swap_out_page(Page *page) {}

void swap_in_page(int page_id) {}

int is_page_on_disk(int page_id) {}

int disk_is_empty() {}

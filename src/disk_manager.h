#ifndef DISK_MANAGER_H
#define DISK_MANAGER_H

#include "page_table.h"

void initialize_disk();
void swap_out_page(Page *page);
void swap_in_page(int page_id);
int is_page_on_disk(int page_id);
int is_page_in_memory(int page_id);
int disk_is_empty();

#endif // DISK_MANAGER_H

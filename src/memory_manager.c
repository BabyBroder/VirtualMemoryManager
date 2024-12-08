#include <stdio.h>
#include <stdlib.h>
#include "memory_manager.h"
#include "page_table.h"
#include "disk_manager.h"

static int *memory = NULL;
static int memory_size = 0;
static int memory_used = 0;

void initialize_memory(int size) {}

void handle_page_fault(int page_id) {}

void add_page_to_memory(int page_id) {}

int is_page_in_memory(int page_id) {}

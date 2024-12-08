#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lru.h"

typedef struct {
    int page;
    int timestamp;
} LRUEntry;

static LRUEntry *table = NULL;
static int capacity = 0;
static int time = 0;

void initialize_lru(int capacity_value) {}

int lru_choose_page_to_replace() {}

void lru_access_page(int page) {}

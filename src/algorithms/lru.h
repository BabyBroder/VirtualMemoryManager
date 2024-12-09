#ifndef LRU_H
#define LRU_H

typedef struct {
    int page;
    int timestamp;
} LRUEntry;

typedef struct {
    LRUEntry *table;
    int capacity;
} LRU;

void initialize_lru(LRU structure, int capacity);
int lru_choose_page_to_replace(LRU structure);
void lru_access_page(LRU structure, int page);
void free_lru(LRU structure);

#endif // LRU_H

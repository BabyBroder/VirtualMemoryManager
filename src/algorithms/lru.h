#ifndef LRU_H
#define LRU_H

void initialize_lru(int capacity);
int lru_choose_page_to_replace();
void lru_access_page(int page);
void free_lru();

#endif // LRU_H

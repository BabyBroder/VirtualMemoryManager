#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

void initialize_memory(int size);
void handle_page_fault(int page_id);
void add_page_to_memory(int page_id);
int is_page_in_memory(int page_id);

#endif // MEMORY_MANAGER_H

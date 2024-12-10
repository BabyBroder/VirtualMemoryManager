#ifndef FIFO_H
#define FIFO_H

void initialize_fifo(int capacity);
int fifo_choose_page_to_replace();
void fifo_add_page(int page);
void free_fifo();

#endif // FIFO_H

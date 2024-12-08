#ifndef FIFO_H
#define FIFO_H

void initialize_fifo(int capacity);
int fifo_choose_page_to_replace();
void fifo_add_page(int page);

#endif // FIFO_H

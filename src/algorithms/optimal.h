#ifndef OPTIMAL_H
#define OPTIMAL_H

void initialize_optimal(int capacity, int *sequence, int sequence_length);
int optimal_choose_page_to_replace(int current_index);
void optimal_add_page(int page);

#endif // OPTIMAL_H

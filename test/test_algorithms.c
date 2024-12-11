#include "../src/algorithms/optimal.h"
#include "../src/algorithms/fifo.h"
#include "../src/algorithms/lru.h"

int main()
{
    FIFO fifo;
    initialize_fifo(&fifo, 3);
    fifo_add_page(&fifo, 1);
    fifo_add_page(&fifo, 2);
    fifo_add_page(&fifo, 3);
    fifo_add_page(&fifo, 4);
    fifo_add_page(&fifo, 5);
    fifo_add_page(&fifo, 6);
    fifo_add_page(&fifo, 7);
    fifo_add_page(&fifo, 8);
    fifo_add_page(&fifo, 9);
    fifo_add_page(&fifo, 10);
    free_fifo(&fifo);

    LRU lru;
    initialize_lru(&lru, 3);
    lru_add_page(&lru, 1);
    lru_add_page(&lru, 2);
    lru_add_page(&lru, 3);
    lru_add_page(&lru, 4);
    lru_add_page(&lru, 5);
    lru_add_page(&lru, 6);
    lru_add_page(&lru, 7);
    lru_add_page(&lru, 8);
    lru_add_page(&lru, 9);
    lru_add_page(&lru, 10);
    free_lru(&lru);

    // add pages in addresses.txt
    Optimal optimal;
    initialize_optimal(&optimal, 3);
    optimal_add_page(&optimal, 34504, 0);
    optimal_add_page(&optimal, 12488, 1);
    optimal_add_page(&optimal, 18376, 2);
    optimal_add_page(&optimal, 45256, 3);
    optimal_add_page(&optimal, 39112, 4);
   
    free_optimal(&optimal);

    return 0;
}
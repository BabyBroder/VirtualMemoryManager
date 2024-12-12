#include "../src/algorithms/optimal.h"
#include "../src/algorithms/fifo.h"
#include "../src/algorithms/lru.h"

void testFIFO(){
    FIFO fifo;
    initialize_fifo(&fifo, 3);
    fifo_add_page(&fifo, 1);
    print_fifo(&fifo);
    fifo_add_page(&fifo, 2);
    print_fifo(&fifo);
    fifo_add_page(&fifo, 3);
    print_fifo(&fifo);
    fifo_add_page(&fifo, 4);
    print_fifo(&fifo);
    fifo_add_page(&fifo, 5);
    print_fifo(&fifo);
    fifo_add_page(&fifo, 6);
    print_fifo(&fifo);
    fifo_add_page(&fifo, 7);
    print_fifo(&fifo);
    fifo_add_page(&fifo, 8);
    print_fifo(&fifo);
    fifo_add_page(&fifo, 9);
    print_fifo(&fifo);
    fifo_add_page(&fifo, 10);
    print_fifo(&fifo);
    free_fifo(&fifo);

}

void testLRU(){
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
}

void testOPT(){
    Optimal optimal;
    initialize_optimal(&optimal, 3);
    optimal_add_page(&optimal, 1, 0);
    optimal_add_page(&optimal, 2, 1);
    optimal_add_page(&optimal, 3, 2);
    optimal_add_page(&optimal, 4, 3);
    optimal_add_page(&optimal, 5, 4);
    optimal_add_page(&optimal, 6, 5);
    optimal_add_page(&optimal, 7, 6);
    optimal_add_page(&optimal, 8, 7);
    optimal_add_page(&optimal, 9, 8);
    optimal_add_page(&optimal, 10, 9);
    free_optimal(&optimal);
}

int main()
{
    testFIFO();
    return 0;
}
#include "../src/algorithms/optimal.h"
#include "../src/algorithms/fifo.h"
#include "../src/algorithms/lru.h"
#include "../src/algorithms/algorithm.h"

void testFIFO(){
    FIFO *fifo;
    fifo = (FIFO *)malloc(sizeof(FIFO));
    initialize_fifo(fifo, 3);
    fifo_add_page(fifo, 1);
    fifo_add_page(fifo, 2);
    fifo_add_page(fifo, 3);
    fifo_add_page(fifo, 4);
    fifo_add_page(fifo, 5);
    fifo_add_page(fifo, 6);
    fifo_add_page(fifo, 7);
    fifo_add_page(fifo, 8);
    fifo_add_page(fifo, 9);
    fifo_add_page(fifo, 10);
    free_fifo(fifo);
}

void testLRU(){
    LRU *lru;
    lru = (LRU *)malloc(sizeof(LRU));
    initialize_lru(lru, 3);
    lru_add_page(lru, 1);
    lru_add_page(lru, 2);
    lru_add_page(lru, 3);
    lru_add_page(lru, 2);
    lru_add_page(lru, 4);
    lru_add_page(lru, 6);
    lru_add_page(lru, 3);
    lru_add_page(lru, 8);
    lru_add_page(lru, 9);
    lru_add_page(lru, 10);
    free_lru(lru);
}

void testOPT(VirtualMemory *virtual_memory){
    Optimal *optimal;
    optimal = (Optimal *)malloc(sizeof(Optimal));
    initialize_optimal(optimal, virtual_memory, 10); // Assuming the third argument is the number of pages
    printf("Optimal initialized\n");
    for(int i = 0; i < ADDRESS_SIZE; i++){
        optimal_add_page(optimal, virtual_memory->address[i], i);
    }
    free_optimal(optimal);
}

int main()
{
    VirtualMemory *virtual_memory = (VirtualMemory *)malloc(sizeof(VirtualMemory));
    initialize_virtual_memory(virtual_memory, "../data/addresses.txt", "BAKING_STORE.BIN");
    printf("Virtual memory initialized\n");
    for(int i = 0; i < ADDRESS_SIZE; i++){
        printf("%d\n", virtual_memory->address[i]);
    }
    printf("Virtual memory address printed\n");
    printf("=====================================\n");
    //testFIFO();
    //testLRU();
    testOPT(virtual_memory);
    return 0;
}

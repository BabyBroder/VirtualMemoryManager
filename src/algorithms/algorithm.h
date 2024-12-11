#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "fifo.h"
#include "lru.h"
#include "optimal.h"

typedef enum {
    FIFO,
    LRU,
    OPT
} Algorithm;

typedef struct {
    FIFO fifo;
    LRU lru;
    Optimal optimal;
} AlgorithmStruct;

#endif // ALGORITHM_H

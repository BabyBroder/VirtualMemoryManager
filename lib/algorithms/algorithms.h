#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "fifo.h"
#include "lru.h"
#include "optimal.h"

/**
 * @enum Algorithm
 * @brief Enumeration of different page replacement algorithms.
 *
 * This enum defines the various page replacement algorithms that can be used
 * in the virtual memory manager.
 *
 * @var FIFO_ALGORITHM
 * First-In-First-Out page replacement algorithm.
 *
 * @var LRU_ALGORITHM
 * Least Recently Used page replacement algorithm.
 *
 * @var OPT_ALGORITHM
 * Optimal page replacement algorithm.
 */
typedef enum
{
    FIFO_ALGORITHM,
    LRU_ALGORITHM,
    OPT_ALGORITHM
} Algorithm;

/**
 * @struct AlgorithmStruct
 * @brief Structure to hold instances of different page replacement algorithms.
 *
 * This structure contains instances of the various page replacement algorithms
 * defined in the Algorithm enum.
 *
 * @var AlgorithmStruct::fifo
 * Instance of the FIFO page replacement algorithm.
 *
 * @var AlgorithmStruct::lru
 * Instance of the LRU page replacement algorithm.
 *
 * @var AlgorithmStruct::optimal
 * Instance of the Optimal page replacement algorithm.
 */
typedef struct
{
    FIFO fifo;
    LRU lru;
    Optimal optimal;
} AlgorithmStruct;

#endif // ALGORITHM_H

#include "algorithms/algorithms.h"
#include "structure/structure.h"
#include "utils/utils.h"
#include "memory/memory.h"
#include "manager/manager.h"

VirtualMemory *virtual_memory;
PhysicalMemory *physical_memory;
TLB *tlb;
PageTable *page_table;
Algorithm algorithm = FIFO_ALGORITHM;

TLBManager *tlb_manager;
PageFaultManager *page_fault_manager;

const char *BACKING_STORE_FILE = "./data/BACKING_STORE.bin";
const char *INPUT_FILE = "./data/addresses.txt";
const char *OUTPUT_FILE = "./data/output.txt";
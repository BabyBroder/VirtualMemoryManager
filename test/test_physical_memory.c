#include "../lib/memory/physical_memory.h"

int main() {
    // Initialize virtual memory
    VirtualMemory* virtualMemory = (VirtualMemory*)malloc(sizeof(VirtualMemory));
    initialize_virtual_memory(virtualMemory, "addresses.txt", "BACKING_STORE.bin");
    //readVirtualMemory(virtualMemory, 0, 0, 256);

    PhysicalMemory* physicalMemoryFiFo = (PhysicalMemory*)malloc(sizeof(PhysicalMemory));
    PhysicalMemory* physicalMemoryLRU = (PhysicalMemory*)malloc(sizeof(PhysicalMemory));
    
    initialize_physical_memory(physicalMemoryFiFo, FIFO_ALGORITHM);
    initialize_physical_memory(physicalMemoryLRU, LRU_ALGORITHM);

    add_page_to_physical_memory(physicalMemoryFiFo, virtualMemory, 0, 0);
    add_page_to_physical_memory(physicalMemoryFiFo, virtualMemory, 1, 1);
    add_page_to_physical_memory(physicalMemoryFiFo, virtualMemory, 2, 2);
    
    read_from_physical_memory(physicalMemoryFiFo, 0, 0);

    return 0;
}
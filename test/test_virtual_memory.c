#include "../lib/memory/virtual_memory.h"

int main() {
    VirtualMemory* virtualMemory = (VirtualMemory*) malloc(sizeof(VirtualMemory));
    initialize_virtual_memory(virtualMemory, "addresses.txt", "BACKING_STORE.bin");
    readVirtualMemory(virtualMemory, 0, 0, 256);

    return 0;
}
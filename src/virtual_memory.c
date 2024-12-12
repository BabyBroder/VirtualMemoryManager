#include "virtual_memory.h"

// Initializes the virtual memory
void initialize_virtual_memory(VirtualMemory *virtual_memory, char* address_file, char* backing_store_file){
    if(virtual_memory->initialized) {
        fprintf(stderr, "Virtual memory already initialized\n");
        return;
    }
    
    virtual_memory->address = (int*)malloc(sizeof(int) * ADDRESS_SIZE);
    if(virtual_memory->address == NULL) {
        perror("Error allocating memory");
        exit(1);
    }

    virtual_memory->data = (char*)malloc(sizeof(char) * BACKING_STORE_SIZE);
    if(virtual_memory->data == NULL) {
        perror("Error allocating memory");
        exit(1);
    }
    
    parser_input_file_int(address_file, virtual_memory->address, ADDRESS_SIZE);
    parser_input_file_data(backing_store_file, virtual_memory->data, BACKING_STORE_SIZE);

    virtual_memory->initialized = true;
}

char *read_BACKINGSTORE(VirtualMemory *virtual_memory, uint32_t virtual_address){
    char* result = (char*)malloc(sizeof(char) * 256);
    const uint16_t PAGE_OFFSET_BITS = 8;
    const uint16_t PAGE_NUMBER_BITS = 16 - PAGE_OFFSET_BITS;

    uint16_t page_number = (virtual_address >> PAGE_OFFSET_BITS) & ((1 << PAGE_NUMBER_BITS) - 1);
    //uint16_t offset = virtual_address & ((1 << PAGE_OFFSET_BITS) - 1);
    
    memcpy(result, &virtual_memory->data[page_number * 256], sizeof(char) * 256);
    return result;
}

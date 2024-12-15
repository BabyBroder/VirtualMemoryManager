#include "../../lib/memory/memory.h"

void initialize_virtual_memory(VirtualMemory *virtual_memory, char *address_file, char *backing_store_file)
{
    if (virtual_memory->initialized)
    {
        fprintf(stderr, "Virtual memory already initialized\n");
        return;
    }

    virtual_memory->address = (int *)malloc(sizeof(int) * ADDRESS_SIZE);
    if (virtual_memory->address == NULL)
    {
        perror("Error allocating memory");
        exit(1);
    }

    virtual_memory->data = (char *)malloc(sizeof(char) * BACKING_STORE_SIZE);
    if (virtual_memory->data == NULL)
    {
        perror("Error allocating memory");
        exit(1);
    }

    parser_input_file_int(address_file, virtual_memory->address, ADDRESS_SIZE);
    parser_input_file_data(backing_store_file, virtual_memory->data, BACKING_STORE_SIZE);

    virtual_memory->initialized = true;
}

char *readVirtualMemory(VirtualMemory *virtual_memory, uint8_t page_number, uint8_t offset, int size)
{
    char *result = (char *)malloc(sizeof(char) * size);

    if (result == NULL)
    {
        perror("Error allocating memory");
        exit(1);
    }

    memcpy(result, &virtual_memory->data[page_number * 256 + offset], sizeof(char) * size);
    return result;
}

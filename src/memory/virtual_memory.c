#include "../../lib/memory/memory.h"

/**
 * @brief Initializes the virtual memory with the provided address and backing store files.
 *
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param address_file The address file to read from.
 * @param backing_store_file The backing store file to read from.
 */
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

/**
 * @brief Reads data from the virtual memory.
 *
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param page_number The page number to read from.
 * @param offset The offset within the page to start reading.
 * @param size The number of bytes to read.
 * @return A pointer to the data read from the virtual memory.
 */
char *readVirtualMemory(VirtualMemory *virtual_memory, uint8_t page_number, uint8_t offset, uint8_t size)
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

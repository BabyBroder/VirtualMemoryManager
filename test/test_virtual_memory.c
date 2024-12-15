#include "../src/main.h"

void print_virtual_memory(VirtualMemory *virtual_memory)
{
    for (int i = 0; i < 256 * 10; i++)
    {
        printf("%02x ", (unsigned char)virtual_memory->data[i]);
        if ((i + 1) % 16 == 0)
        {
            printf("\n");
        }
    }
}

int main()
{
    VirtualMemory *virtualMemory = (VirtualMemory *)malloc(sizeof(VirtualMemory));
    initialize_virtual_memory(virtualMemory, "addresses.txt", "BACKING_STORE.bin");
    print_virtual_memory(virtualMemory);
    return 0;
}
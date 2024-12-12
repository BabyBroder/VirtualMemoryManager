#include "../../lib/manager/manager.h"

/**
 * @brief Initializes the disk manager with the provided virtual memory, physical memory, TLB, page table, and algorithm.
 *
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param physical_memory Pointer to the PhysicalMemory structure.
 * @param tlb Pointer to the TLB structure.
 * @param page_table Pointer to the PageTable structure.
 * @param algorithm The algorithm to be used for managing the disk.
 */
void initialize_disk_manager(VirtualMemory *virtual_memory, PhysicalMemory *physical_memory, TLB *tlb, PageTable *page_table, Algorithm algorithm)
{
    initialize_virtual_memory(virtual_memory, "addresses.txt", "BACKING_STORE.bin");
    initialize_physical_memory(physical_memory, algorithm);
    initialize_tlb(tlb, virtual_memory, algorithm);
    initialize_page_table(page_table);
}

/**
 * @brief Reads data from virtual memory into a frame.
 *
 * @param virtual_memory Pointer to the VirtualMemory structure.
 * @param page_number The page number to read from.
 * @param offset The offset within the page to start reading.
 * @param size The number of bytes to read.
 * @param frame_data Pointer to the buffer where the frame data will be stored.
 */
void read_virutual_memory_to_frame(VirtualMemory *virtual_memory, uint8_t page_number, uint8_t offset, uint16_t size, char *frame_data)
{
    char *data = readVirtualMemory(virtual_memory, page_number, offset, size);
    memcpy(frame_data, data, size);
    free(data);
}
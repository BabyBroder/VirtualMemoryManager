#ifndef MAIN_H
#define MAIN_H

#include "algorithms/algorithms.h"
#include "structure/structure.h"
#include "utils/utils.h"
#include "memory/memory.h"
#include "manager/manager.h"

VirtualMemory *virtual_memory;
PhysicalMemory *physical_memory;
TLB *tlb;
PageTable *page_table;
TLBManager *tlb_manager;
PageFaultManager *page_fault_manager;

Algorithm algorithm_physicalmemory = FIFO_ALGORITHM;
Algorithm algorithm_tlb = FIFO_ALGORITHM;
char *BACKING_STORE_FILE = "./data/BACKING_STORE.bin";
char *INPUT_FILE = "./data/addresses.txt";
char *OUTPUT_FILE = "./data/outputFIFO.txt";
char *LOG_FILE = "./data/output.log";

/**
 * @brief Displays the menu options to the user.
 */
void menu();

/**
 * @brief Parses the command-line arguments.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 */
void parse_arguments(int argc, char *argv[]);

/**
 * @brief Initializes the virtual memory, physical memory, TLB, and page table, TLBmanager, and PageFaultManager.
 *
 * This function initializes the virtual memory, physical memory, TLB, page table and the TLB and page fault managers
 * by allocating memory for each structure and setting up the necessary data structures.
 */
void init();

/**
 * @brief Translates a virtual address to a physical address.
 *
 * This function translates a virtual address to a physical address by extracting the page number
 * and offset from the virtual address and using the page table to find the corresponding frame number.
 * The frame number is then used to calculate the physical address.
 *
 * @param physical_memory The physical memory structure.
 * @param current_index The current index of the virtual memory array.
 */
void _free();

/**
 * @brief Translates a virtual address to a physical address.
 *
 * This function translates a virtual address to a physical address by extracting the page number
 * and offset from the virtual address and using the page table to find the corresponding frame number.
 * The frame number is then used to calculate the physical address.
 *
 * @param physical_memory The physical memory structure.
 * @param current_index The current index of the virtual memory array.
 */
int get_physical_address(int frame_number, int offset);

/**
 * @brief Translates a virtual address to a physical address.
 *
 * This function translates a virtual address to a physical address by extracting the page number
 * and offset from the virtual address and using the page table to find the corresponding frame number.
 * The frame number is then used to calculate the physical address.
 *
 * @param physical_memory The physical memory structure.
 * @param current_index The current index of the virtual memory array.
 */
int get_offset(int virtual_address);

/**
 * @brief Translates a virtual address to a physical address.
 *
 * This function translates a virtual address to a physical address by extracting the page number
 * and offset from the virtual address and using the page table to find the corresponding frame number.
 * The frame number is then used to calculate the physical address.
 *
 * @param physical_memory The physical memory structure.
 * @param current_index The current index of the virtual memory array.
 */
int get_page_number(int virtual_address);

/**
 * @brief Translates a virtual address to a physical address.
 *
 * This function translates a virtual address to a physical address by extracting the page number
 * and offset from the virtual address and using the page table to find the corresponding frame number.
 * The frame number is then used to calculate the physical address.
 *
 * @param physical_memory The physical memory structure.
 * @param current_index The current index of the virtual memory array.
 */
void log_find_page_number(int virtual_address, int current_index, int page_number, bool TLB_hit, bool page_fault);

/**
 * @brief Translates a virtual address to a physical address.
 *
 * This function translates a virtual address to a physical address by extracting the page number
 * and offset from the virtual address and using the page table to find the corresponding frame number.
 * The frame number is then used to calculate the physical address.
 *
 * @param physical_memory The physical memory structure.
 * @param current_index The current index of the virtual memory array.
 */
int get_frame_number(int virtual_address, int current_index);

/**
 * @brief Translates a virtual address to a physical address.
 *
 * This function translates a virtual address to a physical address by extracting the page number
 * and offset from the virtual address and using the page table to find the corresponding frame number.
 * The frame number is then used to calculate the physical address.
 *
 * @param physical_memory The physical memory structure.
 * @param current_index The current index of the virtual memory array.
 */
void translate(PhysicalMemory *physical_memory, int current_index);

/**
 * @brief Translates a virtual address to a physical address.
 *
 * This function translates a virtual address to a physical address by extracting the page number
 * and offset from the virtual address and using the page table to find the corresponding frame number.
 * The frame number is then used to calculate the physical address.
 *
 * @param physical_memory The physical memory structure.
 * @param current_index The current index of the virtual memory array.
 */
void print_results();
#endif // MAIN_H
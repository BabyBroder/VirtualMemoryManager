#include "main.h"

void menu()
{
    printf("Usage: ./vm_manager [OPTIONS]\n\n");
    printf("Options:\n");
    printf("  -h, --help                        Display this help message\n");
    printf("  -d, --default                     Use default values\n");
    printf("  -p, --physical-memory-algorithm   Set the algorithms to use:\n");
    printf("                                    Physical Memory: FIFO, LRU\n");
    printf("  -t, --tlb-algorithm               Set the algorithms to use:\n");
    printf("                                    TLB: FIFO, LRU, OPTIMAL\n");
    printf("  -b, --backing-store               Specify the path to the backing store file\n");
    printf("  -i, --input-file                  Specify the path to the input file\n");
    printf("  -o, --output-file                 Specify the path to the output file\n");
    printf("  -l, --log-file                    Specify the path to the log file\n\n");
    printf("Default values (if no options are specified):\n");
    printf("  Algorithm (Memory):               %s\n", algorithm_physicalmemory == FIFO_ALGORITHM ? "FIFO" : "LRU");
    printf("  Algorithm (TLB):                  %s\n", algorithm_tlb == FIFO_ALGORITHM ? "FIFO" : algorithm_tlb == LRU_ALGORITHM ? "LRU"
                                                                                                                                 : "OPTIMAL");
    printf("  Backing store file:               %s\n", BACKING_STORE_FILE);
    printf("  Input file:                       %s\n", INPUT_FILE);
    printf("  Output file:                      %s\n", OUTPUT_FILE);
    printf("  Log file:                         %s\n", LOG_FILE);
    printf("\n");
}

void parse_arguments(int argc, char *argv[])
{
    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"default", no_argument, 0, 'd'},
        {"physical-memory-algorithm", required_argument, 0, 'p'},
        {"tlb-algorithm", required_argument, 0, 't'},
        {"backing-store", required_argument, 0, 'b'},
        {"input-file", required_argument, 0, 'i'},
        {"output-file", required_argument, 0, 'o'},
        {"log-file", required_argument, 0, 'l'},
        {0, 0, 0, 0} // Sentinel value
    };

    int opt;
    while ((opt = getopt_long(argc, argv, "hdp:t:b:i:o:l:", long_options, NULL)) != -1)
    {
        switch (opt)
        {
        case 'h':
            menu();
            exit(0);

        case 'd':
            printf("[Using default configuration]\n");
            break;

        case 'p':
            if (strcmp(optarg, "FIFO") == 0)
            {
                algorithm_physicalmemory = FIFO_ALGORITHM;
            }
            else if (strcmp(optarg, "LRU") == 0)
            {
                algorithm_physicalmemory = LRU_ALGORITHM;
            }
            else
            {
                fprintf(stderr, "Invalid physical memory algorithm: %s. Supported: FIFO, LRU\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;

        case 't':
            if (strcmp(optarg, "FIFO") == 0)
            {
                algorithm_tlb = FIFO_ALGORITHM;
            }
            else if (strcmp(optarg, "LRU") == 0)
            {
                algorithm_tlb = LRU_ALGORITHM;
            }
            else if (strcmp(optarg, "OPTIMAL") == 0)
            {
                algorithm_tlb = OPT_ALGORITHM;
            }
            else
            {
                fprintf(stderr, "Invalid TLB algorithm: %s. Supported: FIFO, LRU, OPTIMAL\n", optarg);
                exit(EXIT_FAILURE);
            }
            break;

        case 'b':
            BACKING_STORE_FILE = optarg;
            break;

        case 'i':
            INPUT_FILE = optarg;
            break;

        case 'o':
            OUTPUT_FILE = optarg;
            break;

        case 'l':
            LOG_FILE = optarg;
            break;

        default:
            fprintf(stderr, "Invalid option. Use -h or --help for usage.\n");
            exit(EXIT_FAILURE);
        }
    }
}

void init()
{
    virtual_memory = (VirtualMemory *)malloc(sizeof(VirtualMemory));
    if (virtual_memory == NULL)
    {
        printf("Failed to allocate memory for virtual memory\n");
        exit(EXIT_FAILURE);
    }

    physical_memory = (PhysicalMemory *)malloc(sizeof(PhysicalMemory));
    if (physical_memory == NULL)
    {
        printf("Failed to allocate memory for physical memory\n");
        exit(EXIT_FAILURE);
    }

    tlb = (TLB *)malloc(sizeof(TLB));
    if (tlb == NULL)
    {
        printf("Failed to allocate memory for TLB\n");
        exit(EXIT_FAILURE);
    }

    page_table = (PageTable *)malloc(sizeof(PageTable));
    if (page_table == NULL)
    {
        printf("Failed to allocate memory for page table\n");
        exit(EXIT_FAILURE);
    }

    initialize_virtual_memory(virtual_memory, INPUT_FILE, BACKING_STORE_FILE);

    // Algorithm: FIFO or LRU
    initialize_physical_memory(physical_memory, algorithm_physicalmemory);

    // Algorithm: FIFO, LRU or OPTIMAL
    initialize_tlb(tlb, virtual_memory, algorithm_tlb);
    initialize_page_table(page_table);

    tlb_manager = (TLBManager *)malloc(sizeof(TLBManager));
    if (tlb_manager == NULL)
    {
        printf("Failed to allocate memory for TLB manager\n");
        exit(EXIT_FAILURE);
    }

    page_fault_manager = (PageFaultManager *)malloc(sizeof(PageFaultManager));
    if (page_fault_manager == NULL)
    {
        printf("Failed to allocate memory for page fault manager\n");
        exit(EXIT_FAILURE);
    }

    initialize_memory_manager(tlb_manager, page_fault_manager);
}

void _free()
{
    free_virtual_memory(virtual_memory);
    free_page_table(page_table);
}

int get_physical_address(int frame_number, int offset)
{
    return (int)frame_number * FRAME_SIZE + offset;
}

int get_offset(int virtual_address)
{
    return (int)virtual_address & ((1 << OFFSET_BITS) - 1);
}

int get_page_number(int virtual_address)
{
    return (int)(virtual_address >> OFFSET_BITS) & (PAGE_SIZE - 1);
}

void log_find_page_number(int virtual_address, int current_index, int page_number, bool TLB_hit, bool page_fault)
{
    char message[100];
    if (TLB_hit)
    {
        sprintf(message,
                "[HIT ] Address 0x%08X (index %3d), TLB hit: Page number %4d, TLB entry %2d",
                virtual_address, current_index, page_number,
                tlb_lookup(tlb, page_number));
        log_event(LOG_FILE, message);
    }
    else
    {
        sprintf(message,
                "[MISS] Address 0x%08X (index %3d), TLB miss: Page number %4d",
                virtual_address, current_index, page_number);
        log_event(LOG_FILE, message);

        if (page_fault)
        {
            sprintf(message,
                    "[FAULT] Address 0x%08X (index %3d), Page fault: Page number %4d",
                    virtual_address, current_index, page_number);
        }
        else
        {
            sprintf(message,
                    "[HIT ] Address 0x%08X (index %3d), Page table hit: Page number %4d, Page table entry %2d",
                    virtual_address, current_index, page_number,
                    page_table_lookup(page_table, page_number));
        }
        log_event(LOG_FILE, message);
    }
}

int get_frame_number(int virtual_address, int current_index)
{
    bool TLB_hit = false;
    bool page_fault = false;

    int page_number;
    // int offset;
    int frame_number;

    page_number = get_page_number(virtual_address);
    // offset = get_offset(virtual_address);

    frame_number = tlb_check(tlb, tlb_manager, virtual_address, current_index);

    // If TLB miss
    if (frame_number == -1)
    {
        // Check if the page is in the page table
        frame_number = page_table_check(page_table, page_fault_manager, virtual_address, current_index);

        // If Page table miss
        if (frame_number == -1)
        {
            frame_number = add_page_to_physical_memory(physical_memory, virtual_memory, frame_number, page_number);
            link_page_table_to_frame(page_table, page_number, frame_number);
            page_fault = true;
        }
    }
    else
    {
        TLB_hit = true;
    }

    add_entry_to_tlb(tlb, page_number, frame_number, current_index);
    log_find_page_number(virtual_address, current_index, page_number, TLB_hit, page_fault);
    return frame_number;
}

void translate(PhysicalMemory *physical_memory, int current_index)
{
    int virtual_address = virtual_memory->address[current_index];

    // int page_number = get_page_number(virtual_address);
    int offset = get_offset(virtual_address);

    int frame_number = get_frame_number(virtual_address, current_index);
    int physical_address = get_physical_address(frame_number, offset);

    char data = (read_from_physical_memory(physical_memory, frame_number, offset)[0]);

    char output[100];
    sprintf(output, "Virtual address: %d Physical address: %d Value: %d", virtual_address, physical_address, data);
    write_to_output_file(OUTPUT_FILE, output);
}

void print_results()
{
    printf("Input file:                     %-20s\n", INPUT_FILE);
    printf("Output file:                    %-20s\n", OUTPUT_FILE);
    printf("Log file:                       %-20s\n", LOG_FILE);
    printf("Backing store file:             %-20s\n", BACKING_STORE_FILE);
    printf("Algorithm (Physical Memory):    %-20s\n", algorithm_physicalmemory == FIFO_ALGORITHM ? "FIFO" : "LRU");
    printf("Algorithm (TLB):                %-20s\n", algorithm_tlb == FIFO_ALGORITHM ? "FIFO" : algorithm_tlb == LRU_ALGORITHM ? "LRU"
                                                                                                                                : "OPTIMAL");
    printf("TLB hit rate:                   %.2f%%\n",
           (tlb_manager->TLBhits / (float)ADDRESS_SIZE) * 100);
    printf("Page-fault rate:                %.2f%%\n",
           (page_fault_manager->pageFaults / (float)ADDRESS_SIZE) * 100);
}

int main(int argc, char **argv)
{
    parse_arguments(argc, argv);

    init();

    for (int i = 0; i < ADDRESS_SIZE; i++)
    {
        translate(physical_memory, i);
    }

    print_results();
    _free();
    return 0;
}

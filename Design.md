# **Design Document: Virtual Memory Manager**

## **1. Introduction**
- **Purpose**:
  - Describe what the Virtual Memory Manager (VMM) does and structure of its components.
- **Scope**:
  - This system is a lightweight educational implementation of paging, supporting basic memory access, page faults, demanding page, and replacement policies likes FIFO, LRU, OPT.

---

## **2. Architecture Overview**
### **2.1 System Components**
- **Virtual Memory**:
  - Define what virtual memory is and how it is abstracted.
  - Example: "Virtual memory provides an abstraction of large, contiguous memory to processes while using a limited physical memory."
- **Page Table**:
  - Describe the page table and its role.
  - Example: "A page table maps virtual page numbers to physical frames and stores metadata like valid bits and permissions."
- **Physical Memory**:
  - Define the simulated physical memory.
  - Example: "Physical memory is represented as an array of fixed-size frames."

### **2.2 Key Processes**
- **Address Translation**:
  - Explain how virtual addresses are translated into physical addresses.
  - Example: "Each virtual address is split into a virtual page number (VPN) and an offset. The VPN is used to index the page table, and the offset is added to the frame address."
- **Page Fault Handling**:
  - Describe what happens when a page is not in memory.
  - Example: "If a page is not in physical memory, a page fault occurs, triggering the system to load the page from disk into a free frame or replace an existing page."
- **Page Replacement Policy**:
  - Outline the replacement policy, e.g., FIFO, LRU, or Random.
  - Example: "This implementation uses the Least Recently Used (LRU) policy for page replacement."

---

## **3. Functional Requirements**
### **3.1 Address Translation**
- **Input**: Virtual address
- **Output**: Corresponding physical address or page fault.
- **Steps**:
  1. Split the virtual address into VPN and offset.
  2. Check the page table for the frame number.
  3. If valid, construct the physical address; otherwise, trigger a page fault.

### **3.2 Page Fault Handling**
- **Input**: VPN that caused the fault.
- **Output**: Updated page table and physical memory.
- **Steps**:
  1. Identify a free frame or select a frame to replace.
  2. Load the page from disk into the frame.
  3. Update the page table.

---

## **4. Implementation Details**
### **4.1 Data Structures**
- **Page Table**:
  - Example:
    ```c
    typedef struct {
        int frame_number;    // Physical frame number
        bool valid;          // Indicates if the page is in memory
        bool referenced;     // Used for replacement policy
    } PageTableEntry;
    ```
- **Physical Memory**:
  - Example:
    ```c
    typedef struct {
        int frame_id;        // Frame identifier
        bool is_free;        // Indicates if the frame is free
    } Frame;
    ```
- **Queue for Replacement Policy (e.g., FIFO)**:
  - Example:
    ```c
    typedef struct {
        int frame_id;
        struct Node *next;
    } ReplacementQueue;
    ```

### **4.2 Key Algorithms**
- **Address Translation**:
  - Describe the logic of how virtual addresses are converted.
- **Page Fault Handling**:
  - Step-by-step description of how page faults are resolved.
- **Replacement Policy**:
  - Example pseudocode for LRU:
    ```c
    void lru_replace(PageTable *pt, PhysicalMemory *pm) {
        // Find least recently used frame
        int lru_frame = find_lru_frame(pm);
        // Replace page in the frame
        replace_page(pt, lru_frame);
    }
    ```

---

## **5. System Interfaces**
- **Inputs**:
  - Virtual address requests (read/write operations).
- **Outputs**:
  - Physical addresses or page fault signals.
- **System Calls/Commands**:
  - Example:
    ```bash
    ./vmm <input_file>
    ```
  - Input file format: List of memory access requests (`read 0x1234`, `write 0x5678`).

---

## **6. Testing Plan**
- **Test Cases**:
  - Address translation with valid and invalid VPNs.
  - Page fault handling with and without free frames.
  - Page replacement correctness under different policies.
- **Metrics**:
  - Page fault rate.
  - Average memory access time.

---

## **7. Assumptions and Limitations**
- **Assumptions**:
  - Fixed page size, e.g., 4 KB.
  - Physical memory has a limited number of frames.
- **Limitations**:
  - No multithreading support.
  - Disk I/O is simulated and not real.

---

## **8. Future Enhancements**
- Add support for multilevel page tables.
- Implement demand paging with prefetching.
- Introduce support for additional replacement policies (e.g., LFU, Clock).

---

By following this structure, you ensure the `design.md` file is clear, comprehensive, and easy to understand for both developers and reviewers.
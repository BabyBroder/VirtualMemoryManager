Here's a structured **`design.md`** for **Virtual Memory Manager** project.

---

# Virtual Memory Manager - Design Document

## Table of Contents

1. [Overview](#overview)  
2. [Goals and Scope](#goals-and-scope)  
3. [System Design](#system-design)  
   - [High-Level Architecture](#high-level-architecture)  
   - [Key Components](#key-components)  
4. [Workflow](#workflow)
   - [Flow chart](#flow-chart)
   - [Logical Address Translation](#logical-address-translation)  
   - [Page Fault Handling](#page-fault-handling)  
   - [TLB and Page Table Operations](#tlb-and-page-table-operations)  
5. [Data Structures](#data-structures)  
6. [Error Handling](#error-handling)  
7. [Performance Considerations](#performance-considerations)  
8. [Statistics and Output](#statistics-and-output)  
9. [Testing Plan](#testing-plan)  
10. [Future Improvements](#future-improvements)  

---

## 1. Overview

The **Virtual Memory Manager** project simulates the translation of logical addresses to physical addresses using the following mechanisms:  
- **Translation Lookaside Buffer (TLB)** for fast page-to-frame lookups.  
- **Page Tables** to map logical pages to physical frames.  
- **Backing Store** to handle **page faults** when a page is not in memory.  
- **Demand Paging**: Pages are loaded into memory **only when they are needed**, optimizing memory usage.  
- **Page Replacement Strategies**: When physical memory is full, the project uses replacement algorithms to determine which page to evict, including:  
   - **FIFO** (First-In, First-Out)  
   - **LRU** (Least Recently Used)  
   - **OPT** (Optimal Page Replacement)  

The system reads logical addresses from an input file, translates them into physical addresses, retrieves byte values, and outputs the results. Performance statistics, such as **TLB hit rate** and **page fault rate**, are tracked and reported.

---

## 2. Goals and Scope

### Goals:
- Simulate virtual memory address translation.
- Implement TLB and Page Table lookup mechanisms.
- Handle page faults by accessing the **Backing Store**.
- Output results: logical address, physical address, and byte value.
- Generate performance statistics like TLB hit/miss rate and page fault rate.

### Scope:
- Assume a simple **Paging System** with fixed page size.
- Support sequential address lookup from an input file.
- Store pages in a simulated **Physical Memory**.

---

## 3. System Design

### High-Level Architecture
The system follows a step-by-step process:  

1. **Input Handling**: Read logical addresses from a file.  
2. **Address Translation**:  
   - Check TLB for frame number.  
   - If a miss occurs, check the Page Table.  
3. **Page Fault Handling**: Retrieve missing pages from the Backing Store.  
4. **Output Generation**: Report logical address, physical address, and byte value.  
5. **Statistics Collection**: Track page faults, TLB hits/misses, and report at the end.

### Key Components

| Component               | Description                                           |
|-------------------------|-------------------------------------------------------|
| **Logical Address File**| Input file containing logical addresses.              |
| **TLB**                 | A small cache to store recent page-to-frame mappings. |
| **Page Table**          | Data structure mapping pages to frames in memory.     |
| **Backing Store**       | Simulated storage for pages not currently in memory.  |
| **Physical Memory**     | Fixed-size memory storing loaded pages.               |
| **Statistics Generator**| Tracks and reports TLB hits, misses, and page faults. |

---

## 4. Workflow
### Flow chart

![Flow chart](images/flow_chart.png)


### Logical Address Translation
1. **Extract Page Number and Offset** from the logical address.  
2. **Check TLB**:  
   - If the page is in TLB → **TLB Hit** → Retrieve Frame Number.  
   - If the page is not in TLB → **TLB Miss** → Check Page Table.  
3. **Check Page Table**:  
   - If page is found → Retrieve Frame Number.  
   - If not → **Page Fault** → Handle Page Fault.  
4. **Translate to Physical Address**: Combine Frame Number and Offset.  
5. Retrieve the Byte Value from Physical Memory.

### Page Fault Handling

<!-- 1. Access the **Backing Store** to load the required page.  
2. Store the page in **Physical Memory**.  
3. Update both the **Page Table** and **TLB**.  
4. Retry the address translation. -->


We implement **demand paging**, where pages are loaded into physical memory only when they are needed (i.e., on a **page fault**). This ensures efficient use of memory and avoids preloading unnecessary pages.

When physical memory is full and a new page needs to be loaded, we use **page replacement strategies** to determine which page to evict. The following strategies are supported:

1. **FIFO (First-In, First-Out)**:  
   - Evicts the oldest page that was loaded into memory.  
   - Simple to implement and efficient for sequential access patterns.

2. **LRU (Least Recently Used)**:  
   - Evicts the page that has not been used for the longest time.  
   - Tracks page access history to approximate optimal performance.

The chosen page replacement strategy can be configured during runtime or testing.

### TLB and Page Table Operations
- **TLB Update**: Use a **FIFO** or **LRU** replacement policy for TLB entries.  
- **Page Table Update**: Add mappings for pages loaded during a page fault.

---

## 5. Data Structures

| Data Structure           | Description                                              |
|--------------------------|----------------------------------------------------------|
| **TLB**                  | Small, fixed-size array storing recent page-to-frame mappings. |
| **Page Table**           | Array mapping logical page numbers to physical frames.   |
| **Backing Store**        | Simulated disk holding all pages (e.g., binary file).    |
| **Physical Memory**      | Array representing the fixed-size memory.               |

---

## 6. Error Handling
- **Invalid Logical Address**: Skip the address and log a warning.  
- **Backing Store Access Failure**: Report and exit gracefully.  
- **Memory Overflow**: Replace pages using a simple replacement policy (e.g., FIFO).

---

## 7. Performance Considerations
- **TLB Hit Rate**: Minimize TLB misses using effective replacement policies.  
- **Page Fault Rate**: Efficiently handle page faults to minimize overhead.  
- **Memory Management**: Limit physical memory usage with a replacement strategy.

---

## 8. Statistics and Output
### Metrics:
- TLB Hit Count / TLB Miss Count  
- Page Fault Count  
- Overall Address Translations  

### Output Format:
For each logical address, output:  
```
Logical Address: X, Physical Address: Y, Value: Z
```

At the end, report:  
```
TLB Hit Rate: XX%, Page Fault Rate: YY%
```

---

## 9. Testing Plan

### Test Scenarios:
1. **Basic Translation**: Logical addresses without page faults.  
2. **Page Fault Handling**: Simulate addresses causing page faults.  
3. **TLB Operations**: Validate TLB updates and replacement.  
4. **Edge Cases**: Invalid addresses, large input files, etc.

### Tools:
- Input Address File Generator  
- Unit Testing for each component (TLB, Page Table, etc.).

---

## 10. Future Improvements
- Implement **LRU** replacement policy for TLB.  
- Optimize Backing Store access time.  
- Extend to multi-threaded virtual memory management.  
- Simulate demand paging algorithms (e.g., **FIFO**, **LRU**).  

---

### End of Document

This structure will guide your project's design, ensuring clarity and completeness. Let me know if you'd like further refinements or additional details!
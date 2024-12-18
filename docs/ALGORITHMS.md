# Algorithms Virtual Memory Manager

# FIFO Algorithm (First-In-First-Out)

The **FIFO (First-In-First-Out)** algorithm is applied when **TLB hits** or **page-table faults** occurs. The first item added is the first one to be removed.  

## FIFO Implementation:
1. Before adding a page to the queue, check if the page already exists in the queue. If it does, skip the current page and do not modify the queue.
2. If the queue has space available, add the page to the end of the queue.
3. If the queue is full, remove the element at the front of the queue (the oldest element) and add the page to the end of the queue.

## FIFO Structure:
1. **int \*queue:**
    - A pointer to the dynamically allocated array that stores the queue elements.
2. **int capacity:**
    - The maximum number of elements the queue can hold.
3. **int front:**
    - The index of the front element in the queue (the oldest element to be removed first).
4. **int rear:**
    - The index where the next element will be added in the queue.
5. **int size**
    - The current number of elements present in the queue.

## FIFO FLowChart When Adding The Page

![FIFO Flowchart](../images/Algorithms/FIFO.png)

## Example of FIFO Algorithm:
In a virtual memory system with FIFO page replacement:
- Capacity is **3**.
- Pages arrive in this order: **1, 2, 3, 2, 4, 3, 1**.

#### Steps:
1. Add **1** → Memory: `[1]`
2. Add **2** → Memory: `[1, 2]`
3. Add **3** → Memory: `[1, 2, 3]`
4. Add **2** (already in memory, no replacement) → Memory: `[1, 2, 3]`
5. Add **4** (replace the oldest, **1**) → Memory: `[2, 3, 4]`
6. Add **3** (already in memory, no replacement) → Memory: `[2, 3, 4]`
7. Add **1** (replace the oldest, **2**) → Memory: `[3, 4, 1]`

# LRU (Least Recently Used)
The **LRU (Least Recently Used)** algorithm is applied when **TLB hits** or **page-table faults** occur. It replaces the page that has not been used for the longest time, assuming it is the least likely to be accessed again soon.

## LRU Implementation:
1. Use the variable '**time**' to store the time each page is used.
2. Before adding a page to the queue, increase '**time**'.
3. Check if the page already exists in the queue. If it does, update its usage time to '**time**'.
4. If the page does not exist and the queue has space available, add the page to the queue and set its usage time to '**time**'.
5. If the queue is full, find the least recently used page and replace it with the new page.

## LRU Structure:
1. **LRUEntry \*table:**
    - A pointer to the dynamically allocated array that stores the page number and the timestamp indicating the least recently used.
2. **unsigned long time:**
    - The current time used for timestamping entries.
3. **int capacity:**
    - The maximum number of entries the LRU cache can hold.
4. **int size:**
    - The current number of entries in the LRU cache.

## LRU FLowChart When Adding The Page

![LRU Flowchart](../images/Algorithms/LRU.png)

## Example of LRU Algorithm:
In a virtual memory system with LRU page replacement:
- Capacity is **3**.
- Pages arrive in this order: **1, 2, 3, 2, 4, 1**.

#### Steps:
1. Add **1** → Memory: `[1]`
2. Add **2** → Memory: `[1, 2]`
3. Add **3** → Memory: `[1, 2, 3]`
4. Access **2** (hit) → Memory: `[1, 3, 2]`
5. Add **4** (miss, replace least recently used **1**) → Memory: `[3, 2, 4]`
6. Add **1** (miss, replace least recently used **3**) → Memory: `[2, 4, 1]`
7. Final Memory State → Memory: `[2, 4, 1]`

# Optimal Page Replacement Algorithm

The **Optimal Page Replacement** algorithm is a page replacement strategy used in memory management. It replaces the page that will not be used for the longest period in the future. This approach minimizes the number of page faults, making it the most efficient page replacement strategy theoretically.

## OPT Implementation:
1. When adding the page, check if the page already exists in the queue. If it does, skip the current page and do not modify the queue.
2. If the queue has space available, add the page to the queue.
3. If the queue is full, find the   .

## OPT FLowChart When Adding The Page
![OPT Flowchart](../images/Algorithms/OPT.png)

## OPT Structure
1. **int \*page:**
    - Array to store the pages currently in memory
2. **int capacity:**
    - The maximum number of elements the queue can hold.
3. **int size:**
    - Current number of pages in memory
4. **int \*future_usage:**
    - Array to track future usage of pages

## Example of OPT Algorithm
- Capacity is **3**.
- Page request sequence: **1, 2, 3, 2, 4, 1, 5**.

### Steps:
1. Request **1** → Add to memory → Memory: `[1]`.
2. Request **2** → Add to memory → Memory: `[1, 2]`.
3. Request **3** → Add to memory → Memory: `[1, 2, 3]`.
4. Request **2** → Already in memory (no replacement).
5. Request **4** → Replace **1** (farthest future use) → Memory: `[4, 2, 3]`.
6. Request **1** → Replace **3** (farthest future use) → Memory: `[4, 2, 1]`.
7. Request **5** → Replace **2** (farthest future use) → Memory: `[4, 5, 1]`.

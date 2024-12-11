# Algorithms Virtual Memory Manager

# FIFO Algorithm (First-In-First-Out)

The **FIFO (First-In-First-Out)** algorithm is applied when **TLB hits** or **page-table faults** occurs. The first item added is the first one to be removed.  

### Function in FIFO:
1. **Enqueue (Add to Queue)**: Add items to the back of the queue.
2. **Dequeue (Remove from Queue)**: Remove items from the front of the queue.
3. **Processing Order**: Items are processed in the same order they arrive, ensuring fairness.

### Memory Management Example:
In a virtual memory system with FIFO page replacement:
- Assume the memory can hold 3 pages.
- Pages arrive in this order: **1, 2, 3, 4**.

#### Steps:
1. Add **1** → Memory: `[1]`
2. Add **2** → Memory: `[1, 2]`
3. Add **3** → Memory: `[1, 2, 3]`
4. Add **4** (replace the oldest, **1**) → Memory: `[2, 3, 4]`

# LRU (Least Recently Used)
The **LRU (Least Recently Used)** algorithm is applied when **TLB hits** or **page-table faults** occur. It replaces the page that has not been used for the longest time, assuming it is the least likely to be accessed again soon.
### Function in LRU:
1. **Access Page**: When a page is accessed, move it to the most recently used position.
2. **Replace Page**: When memory is full and a new page is requested, replace the least recently used page.
### Memory Management Example:
In a virtual memory system with LRU page replacement:
- Assume the memory can hold 3 pages.
- Pages arrive in this order: **1, 2, 3, 1, 4, 5**.

#### Steps:
1. Add **1** → Memory: `[1]`
2. Add **2** → Memory: `[1, 2]`
3. Add **3** → Memory: `[1, 2, 3]`
4. Access **1** (hit) → Memory: `[2, 3, 1]`
5. Add **4** (miss, replace least recently used **2**) → Memory: `[3, 1, 4]`
6. Add **5** (miss, replace least recently used **3**) → Memory: `[1, 4, 5]`

# Optimal Page Replacement Algorithm

The **Optimal Page Replacement** algorithm is a page replacement strategy used in memory management. It replaces the page that will not be used for the longest period in the future. This approach minimizes the number of page faults, making it the most efficient page replacement strategy theoretically.

### Function in OPT:
1. **Track Future Usage**: The algorithm uses knowledge of future page requests to decide which page to replace. Builds the table to map pages to their future access indices. Ensures efficient access to determine which page will be used farthest in the future.
2. **Replace Page**: When memory is full, finds the page in memory that will not be used for the longest period in the future to replace. If a page will not be used again, it is immediately selected for replacement. Otherwise, it identifies the page with the farthest future access index.

### Memory Management Example:
- Memory can hold 3 pages.
- Page request sequence: **1, 2, 3, 2, 4, 1, 5**.

### Steps:
1. Request **1** → Add to memory → Memory: `[1]`.
2. Request **2** → Add to memory → Memory: `[1, 2]`.
3. Request **3** → Add to memory → Memory: `[1, 2, 3]`.
4. Request **2** → Already in memory (no replacement).
5. Request **4** → Replace **1** (farthest future use) → Memory: `[4, 2, 3]`.
6. Request **1** → Replace **3** (farthest future use) → Memory: `[4, 2, 1]`.
7. Request **5** → Replace **2** (farthest future use) → Memory: `[4, 5, 1]`.

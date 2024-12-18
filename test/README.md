This test implements and tests various components of a memory management system, including virtual memory, physical memory, page tables, TLBs, and algorithms such as FIFO, LRU, and Optimal.
# How to Build
To compile the project and create test binaries:
- Open a terminal in the project directory.
- Run the following command to build all test binaries:
    ```
    make test_*.c
    ```

# How to Run Tests
To run all tests:
- Build the project as described above.
- Run all test binaries with:
    ```
    make run_tests
    ```

To run a specific test binary:
```
./<test_binary_name>
```

For example:
```
./test_virtual_memory
```

# How to clean
To remove all generated binaries:
```
make clean
```

# Notes
- We enable test-specific configurations by using the -DTEST flag in the Makefile.
- If you encounter any issues, check the Makefile or dependencies.
# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I src -I ../src/utils -I ../src/algorithms
LDFLAGS = 

# Test binaries
TESTS = test_memory_manager test_page_table test_disk_manager test_algorithms test_tlb

# Core sources
SRC = ../src/memory_manager.c ../src/page_table.c ../src/disk_manager.c \
      ../src/tlb.c ../src/physical_memory.c ../src/virtual_memory.c \
      ../src/utils/logger.c ../src/utils/parser.c \
      ../src/algorithms/fifo.c ../src/algorithms/lru.c ../src/algorithms/optimal.c

# Test sources
TEST_SRC = test_memory_manager.c test_page_table.c \
           test_disk_manager.c test_algorithms.c test_tlb.c

# Targets
all: $(TESTS)

# Compile each test binary
test_memory_manager: test_memory_manager.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_page_table: test_page_table.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_disk_manager: test_disk_manager.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_algorithms: test_algorithms.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_tlb: test_tlb.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Run all tests
run_tests: $(TESTS)
	@echo "Running all tests..."
	@for test in $(TESTS); do \
		echo "Running $$test..."; \
		./$$test; \
	done
	@echo "All tests completed."

# Clean up binaries
clean:
	rm -f $(TESTS)

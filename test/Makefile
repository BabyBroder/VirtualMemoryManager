# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -I ../lib -I ../lib/algorithms -I ../lib/manager -I ../lib/memory -I ../lib/structure -I ../lib/utils
LDFLAGS =

# Test binaries
TESTS = test_memory_manager test_page_table test_disk_manager test_algorithms test_tlb

# Core sources
SRC = ../src/manager/memory_manager.c ../src/structure/page_table.c ../src/manager/disk_manager.c \
      ../src/structure/tlb.c ../src/memory/physical_memory.c ../src/memory/virtual_memory.c \
      ../src/utils/logger.c ../src/utils/parser.c \
      ../src/algorithms/fifo.c ../src/algorithms/lru.c ../src/algorithms/optimal.c

# Test sources
TEST_SRC = test_memory_manager.c test_page_table.c \
           test_disk_manager.c test_algorithms.c test_tlb.c

# Targets
all: $(TESTS)

# Compile each test binary
test_physical_memory: test_physical_memory.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	
test_virtual_memory: test_virtual_memory.c $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

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
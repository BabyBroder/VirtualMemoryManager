# Compiler and flags
CC = gcc
CFLAGS = -DTEST -Wall -g -I ../lib -I ../lib/algorithms -I ../lib/manager -I ../lib/memory -I ../lib/structure -I ../lib/utils
LDFLAGS =

# Test binaries
TESTS = test_memory_manager test_page_table test_disk_manager test_algorithms test_tlb test_physical_memory test_virtual_memory

SRC_LOGGER = ../src/utils/logger.c

SRC_PARSER = ../src/utils/parser.c

SRC_VIRTUAL_MEMORY = ../src/memory/virtual_memory.c $(SRC_LOGGER) $(SRC_PARSER)

SRC_ALGORITHMS =    ../src/algorithms/fifo.c ../src/algorithms/lru.c ../src/algorithms/optimal.c \
					$(SRC_VIRTUAL_MEMORY)

SRC_PHYSICAL_MEMORY = ../src/memory/physical_memory.c $(SRC_ALGORITHMS)

SRC_MEMORY_MANAGER = ../src/manager/memory_manager.c

SRC_PAGE_TABLE = ../src/structure/page_table.c

SRC_TLB = ../src/structure/tlb.c $(SRC_PAGE_TABLE) $(SRC_ALGORITHMS)

SRC_DISK_MANAGER = ../src/manager/disk_manager.c $(SRC_MEMORY_MANAGER) $(SRC_PHYSICAL_MEMORY) $(SRC_TLB)



# Test sources
TEST_SRC = test_memory_manager.c test_page_table.c \
           test_disk_manager.c test_algorithms.c test_tlb.c

# Targets
all: $(TESTS)

# Compile each test binary	

test_logger: test_logger.c $(SRC_LOGGER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_parser: test_parser.c $(SRC_PARSER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_virtual_memory: test_virtual_memory.c $(SRC_VIRTUAL_MEMORY)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_algorithms: test_algorithms.c $(SRC_ALGORITHMS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_physical_memory: test_physical_memory.c $(SRC_PHYSICAL_MEMORY)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_memory_manager: test_memory_manager.c $(SRC_MEMORY_MANAGER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_disk_manager: test_disk_manager.c $(SRC_DISK_MANAGER)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_page_table: test_page_table.c $(SRC_PAGE_TABLE)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

test_tlb: test_tlb.c $(SRC_TLB)
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
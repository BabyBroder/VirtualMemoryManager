CC = gcc
CFLAGS = -Wall -g -I src -I src/utils -I src/algorithms
LDFLAGS = 

TARGET = vm_manager

SRC = src/main.c src/memory_manager.c src/page_table.c src/disk_manager.c \
      src/tlb.c src/physical_memory.c src/virtual_memory.c \
      src/utils/logger.c src/utils/parser.c \
      src/algorithms/fifo.c src/algorithms/lru.c src/algorithms/optimal.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJ)

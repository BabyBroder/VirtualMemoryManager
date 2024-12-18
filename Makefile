CC = gcc
CFLAGS = -Wall -g -I lib -I lib/algorithms -I lib/manager -I lib/memory -I lib/structure -I lib/utils -I src/algorithms
LDFLAGS =

TARGET = vm_manager

SRC = src/main.c \
      src/manager/memory_manager.c src/manager/disk_manager.c \
      src/structure/page_table.c src/structure/tlb.c \
      src/memory/physical_memory.c src/memory/virtual_memory.c \
      src/utils/logger.c src/utils/parser.c \
      src/algorithms/fifo.c src/algorithms/lru.c src/algorithms/optimal.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean_output:
	rm -f data/output*.txt
	rm -f data/output*.log

clean:
	rm -f $(TARGET) $(OBJ)
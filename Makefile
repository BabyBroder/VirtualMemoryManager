CC = gcc
CFLAGS = -Wall -g
SOURCES = src/main.c src/memory_manager.c src/page_table.c src/disk_manager.c \
          src/algorithms/fifo.c src/algorithms/lru.c src/algorithms/optimal.c \
          src/utils/logger.c src/utils/parser.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = vm_manager

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET) $(OBJECTS)

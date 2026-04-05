CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -g -O0
PTHREAD_FLAGS = -pthread
BIN_DIR = bin

MEMORY_BINS = \
	$(BIN_DIR)/memory_leak_bug \
	$(BIN_DIR)/double_free_bug \
	$(BIN_DIR)/realloc_misuse_bug

CONCURRENCY_BINS = \
	$(BIN_DIR)/race_condition_bug \
	$(BIN_DIR)/deadlock_bug \
	$(BIN_DIR)/shared_buffer_bug

DATA_STRUCTURE_BINS = \
	$(BIN_DIR)/linked_list_leak_bug \
	$(BIN_DIR)/linked_list_use_after_free_bug

ALL_BINS = $(MEMORY_BINS) $(CONCURRENCY_BINS) $(DATA_STRUCTURE_BINS)

all: $(BIN_DIR) $(ALL_BINS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/memory_leak_bug: memory/memory_leak_bug.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/double_free_bug: memory/double_free_bug.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/realloc_misuse_bug: memory/realloc_misuse_bug.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/race_condition_bug: concurrency/race_condition_bug.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(BIN_DIR)/deadlock_bug: concurrency/deadlock_bug.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(BIN_DIR)/shared_buffer_bug: concurrency/shared_buffer_bug.c
	$(CC) $(CFLAGS) $(PTHREAD_FLAGS) $< -o $@

$(BIN_DIR)/linked_list_leak_bug: data_structures/linked_list_leak_bug.c
	$(CC) $(CFLAGS) $< -o $@

$(BIN_DIR)/linked_list_use_after_free_bug: data_structures/linked_list_use_after_free_bug.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: all clean

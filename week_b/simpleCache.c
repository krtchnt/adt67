#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
  int data;
  int mem_addr;
} cell_t;

typedef struct hash {
  cell_t *table;
  int cache_size;
} hash_t;

typedef hash_t cache_t;
typedef int memory_t;
memory_t *init_memory(int size) {
  memory_t *memory = (memory_t *)malloc(sizeof(memory_t) * size);
  int i = 0;

  // Randomly assign integers to memory
  for (i = 0; i < size; i++)
    memory[i] = rand();
  return memory;
}

cache_t *init_cache(const unsigned long cache_size);
void get_data(const unsigned long addr, const memory_t *memory, cache_t *cache);

int main(void) {
  memory_t *memory = NULL;
  cache_t *cache = NULL;
  int memory_size, cache_size;
  int i, n, addr;

  scanf("%d %d %d", &memory_size, &cache_size, &n);

  memory = init_memory(memory_size);
  cache = init_cache(cache_size);

  for (i = 0; i < n; i++) {
    printf("Load address: ");
    scanf("%d", &addr);
    get_data(addr, memory, cache);
  }
  return 0;
}

cache_t *init_cache(const unsigned long cache_size) {
  cache_t *cache = (cache_t *)malloc(sizeof(cache_t));
  cache->table = (cell_t *)calloc(cache_size, sizeof(cell_t));
  cache->cache_size = cache_size;
  return cache;
}

void get_data(const unsigned long addr, const memory_t *memory,
              cache_t *cache) {
  const unsigned long i = addr % cache->cache_size;
  const memory_t mem_data = memory[addr];
  cell_t *cell = cache->table + i;

  if (!cell->mem_addr && !cell->data) {
    printf("Load from memory\n");
    cell->data = mem_data;
    cell->mem_addr = addr;
  } else if (cell->mem_addr != addr || cell->data != mem_data) {
    printf("Index: %lu is used\n", i);
    printf("Load from memory\n");
    cell->data = mem_data;
    cell->mem_addr = addr;
  } else {
    printf("Address %lu is loaded\n", addr);
  }

  printf("Data: %i\n", cell->data);
}

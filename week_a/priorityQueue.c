#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
  int *data;
  int last_index;
} heap_t;

heap_t *init_heap(const int m);
void insert(heap_t *h, const int data);
void delete_max(heap_t *h);
int find_max(const heap_t *h);
void update_key(heap_t *h, const int old_key, const int new_key);
void bfs(const heap_t *h);

int main(void) {
  heap_t *max_heap = NULL;
  int m, n, i;
  int command, data;
  int old_key, new_key;

  scanf("%d %d", &m, &n);
  max_heap = init_heap(m);
  for (i = 0; i < n; i++) {
    scanf("%d", &command);
    switch (command) {
    case 1:
      scanf("%d", &data);
      insert(max_heap, data);
      break;
    case 2:
      delete_max(max_heap);
      break;
    case 3:
      printf("%d\n", find_max(max_heap));
      break;
    case 4:
      scanf("%d %d", &old_key, &new_key);
      update_key(max_heap, old_key, new_key);
      break;
    case 5:
      bfs(max_heap);
      break;
    }
  }
  return 0;
}

heap_t *init_heap(const int m) {
  heap_t *h = (heap_t *)malloc(sizeof(heap_t));
  h->data = (int *)malloc(sizeof(int) * m);
  h->last_index = -1;
  return h;
}

void swap(int *a, int *b) {
  int c = *a;
  *a = *b;
  *b = c;
}

void heapify_u(heap_t *h, int i) {
  int j = (i - 1) / 2;
  if (i > 0 && h->data[i] > h->data[j]) {
    swap(&h->data[i], &h->data[j]);
    heapify_u(h, j);
  }
}

void insert(heap_t *h, const int data) {
  h->data[++h->last_index] = data;
  heapify_u(h, h->last_index);
}

void heapify_d(heap_t *h, int i) {
  int m = i, l = 2 * i + 1, r = 2 * i + 2;
  if (l <= h->last_index && h->data[l] > h->data[m])
    m = l;
  if (r <= h->last_index && h->data[r] > h->data[m])
    m = r;
  if (m != i) {
    swap(&h->data[i], &h->data[m]);
    heapify_d(h, m);
  }
}

void delete_max(heap_t *h) {
  h->data[0] = h->data[h->last_index--];
  heapify_d(h, 0);
}

void update_key(heap_t *h, const int old_key, const int new_key) {
  int i = -1;
  for (int j = 0; j <= h->last_index; j++)
    if (h->data[j] == old_key) {
      i = j;
      break;
    }

  if ((h->data[i] = new_key) > old_key)
    heapify_u(h, i);
  else
    heapify_d(h, i);
}

int find_max(const heap_t *h) { return h->last_index < 0 ? -1 : h->data[0]; }

void bfs(const heap_t *h) {
  for (int i = 0; i <= h->last_index; i++)
    printf("%d ", h->data[i]);
  putchar('\n');
}

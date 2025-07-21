#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
  long *data;
  unsigned long len;
} heap_t;

heap_t *new(const unsigned long n);
double median(heap_t *g, heap_t *s, const long d);
void free_heap(heap_t *h);

int main(void) {
  unsigned long n;
  scanf("%lu", &n);
  heap_t *g = new (n);
  heap_t *s = new (n);
  for (unsigned long i = 0; i < n; i++) {
    long d;
    scanf("%li", &d);
    double med = median(g, s, d);
    printf("%.1lf\n", med);
  }
  free_heap(g);
  free_heap(s);
  return 0;
}

heap_t *new(const unsigned long n) {
  heap_t *h = (heap_t *)malloc(sizeof(heap_t));
  h->data = (long *)malloc(sizeof(long) * n);
  h->len = 0;
  return h;
}
void free_heap(heap_t *h) {
  free(h->data);
  free(h);
}
void swp(long *a, long *b) {
  long c = *a;
  *a = *b;
  *b = c;
}

void heapify_u(heap_t *h, int i) {
  int j = (i - 1) / 2;
  if (i > 0 && h->data[i] > h->data[j]) {
    swp(&h->data[i], &h->data[j]);
    heapify_u(h, j);
  }
}

void insert(heap_t *h, const long d) {
  h->data[h->len++] = d;
  heapify_u(h, h->len - 1);
}

void heapify_d(heap_t *h, int i) {
  int m = i, l = 2 * i + 1, r = 2 * i + 2;
  if (l < h->len && h->data[l] > h->data[m])
    m = l;
  if (r < h->len && h->data[r] > h->data[m])
    m = r;
  if (m != i) {
    swp(&h->data[i], &h->data[m]);
    heapify_d(h, m);
  }
}

void delete_max(heap_t *h) {
  h->data[0] = h->data[--h->len];
  heapify_d(h, 0);
}

long find_max(const heap_t *h) { return h->data[0]; }

double median(heap_t *g, heap_t *s, const long d) {
  insert(s, d);
  long t = find_max(s);
  delete_max(s);

  insert(g, -t);
  if (g->len > s->len) {
    t = find_max(g);
    delete_max(g);
    insert(s, -t);
  }
  if (g->len != s->len)
    return (double)find_max(s);
  return ((double)find_max(s) - (double)find_max(g)) / 2.0;
}

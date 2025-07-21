#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vec {
  unsigned long *arr;
  unsigned long cap;
  unsigned long len;
} vec_t;

vec_t new();
void grow(vec_t *v);
void push(vec_t *v, const unsigned long c);
unsigned long peek(const vec_t *v);
unsigned long pop(vec_t *v);
bool is_empty(vec_t *v);

bool is_stack_sortable(const unsigned long *arr, const unsigned long n);

int main(void) {
  unsigned long n;
  scanf("%lu", &n);

  unsigned long *parade = (unsigned long *)malloc(n * sizeof(unsigned long));
  for (unsigned long i = 0; i < n; i++) scanf("%lu", parade + i);

  bool stack_sortable = is_stack_sortable(parade, n);
  printf("%u", stack_sortable);
  return 0;
}

bool is_stack_sortable(const unsigned long *arr, const unsigned long n) {
  vec_t v = new();
  unsigned long next = 1;

  for (unsigned long i = 0; i < n; i++) {
    unsigned long m = arr[i];

    while (!is_empty(&v) && peek(&v) == next) { pop(&v); next++; }
    if (m == next) { next++; continue; }
    push(&v, m);
  }

  while (!is_empty(&v)) { if (pop(&v) != next) return false; next++;}
  return true;
}

vec_t new() {
  const vec_t v = {NULL, 0, 0};
  return v;
}

void grow(vec_t *v) {
  if (!v->cap) {
    v->cap = 1;
    v->arr = (unsigned long*)malloc(sizeof(unsigned long));
    return;
  }
  v->cap *= 2;
  v->arr = reallocarray(v->arr, v->cap, sizeof(unsigned long));
}

void push(vec_t *v, const unsigned long m) {
  if (v->cap == v->len) grow(v);
  v->arr[v->len++] = m;
}

unsigned long peek(const vec_t *v) { return v->arr[v->len-1]; }

unsigned long pop(vec_t *v) {
  unsigned long top = v->arr[--v->len];
  return top;
}

bool is_empty(vec_t *v) { return !v->len; }

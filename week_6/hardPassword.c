#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vec {
  char *arr;
  unsigned cap;
  unsigned len;
} vec_t;

vec_t new();
void grow(vec_t *v);
void push(vec_t *v, const char c);
char pop(vec_t *v);
bool is_empty(vec_t *v);

int main(void) {
  vec_t v = new();
  bool incorrect = false;

  char c;
  while ((c = getchar()) != 'x') push(&v, c);
  while ((c = getchar()) != 'y' && !incorrect) {
    if (is_empty(&v) || pop(&v) != c) { incorrect = true; }
  }

  putchar((!incorrect && is_empty(&v)) ? '1' : '0');
  return 0;
}

vec_t new() {
  const vec_t v = {NULL, 0, 0};
  return v;
}

void grow(vec_t *v) {
  if (!v->cap) {
    v->cap = 1;
    v->arr = (char *)malloc(sizeof(char));
    return;
  }
  v->cap *= 2;
  v->arr = reallocarray(v->arr, v->cap, sizeof(char));
}

void push(vec_t *v, const char c) {
  if (v->cap == v->len) grow(v);
  v->arr[v->len++] = c;
}

char pop(vec_t *v) {
  char top = v->arr[--v->len];
  return top;
}

bool is_empty(vec_t *v) { return !v->len; }

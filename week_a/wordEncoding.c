#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree {
  char *str;
  int freq;
  struct tree *left;
  struct tree *right;
} tree_t;
typedef tree_t node_t;

typedef struct heap {
  tree_t **data;
  int len;
} heap_t;

heap_t *new_heap(const int m);
tree_t *new_tree(const char *s, const int f);
void push(heap_t *h, tree_t *t);
void meld(heap_t *h);
void print(const tree_t *t);

int main(void) {
  unsigned long n;

  scanf("%lu", &n);
  heap_t *h = new_heap(n);
  for (int i = 0; i < n; i++) {
    unsigned freq;
    char c[15 + 1];
    scanf("%s %u", c, &freq);
    push(h, new_tree(c, freq));
  }

  meld(h);
  print(h->data[1]);
  return 0;
}

heap_t *new_heap(const int m) {
  heap_t *h = (heap_t *)malloc(sizeof(heap_t));
  h->data = (tree_t **)malloc((m + 1) * sizeof(tree_t *));
  h->len = 0;
  return h;
}

tree_t *new_tree(const char *s, const int freq) {
  tree_t *t = (tree_t *)malloc(sizeof(tree_t));
  t->left = t->right = NULL;
  t->freq = freq;
  t->str = (char *)malloc((strlen(s) + 1) * sizeof(char));
  strcpy(t->str, s);
  return t;
}

void swp(heap_t *h, const int i, const int j) {
  tree_t *n = h->data[i];
  h->data[i] = h->data[j];
  h->data[j] = n;
}

void push(heap_t *h, tree_t *t) {
  h->data[++h->len] = t;
  for (int c = h->len, f = c; c > 1; swp(h, c, f), c = f)
    if (h->data[(f >>= 1)]->freq <= h->data[c]->freq)
      break;
}

int top(const heap_t *h, const int z, const int g) {
  const int l = 2 * z, r = 2 * z + 1;

  if (l > g && r > g)
    return -1;
  if (l > g)
    return r;
  if (r > g)
    return l;
  return h->data[l]->freq > h->data[r]->freq ? r : l;
}

tree_t *pop(heap_t *h) {
  if (h->len == 0)
    return NULL;
  if (h->len == 1) {
    --h->len;
    return h->data[1];
  }
  tree_t *t = h->data[1];
  h->data[1] = h->data[h->len--];
  for (int c = 1, f = c; (f = top(h, c, h->len)) != -1; swp(h, c, f), c = f)
    if (h->data[c]->freq <= h->data[f]->freq)
      break;
  return t;
}

tree_t *merge(tree_t *t, tree_t *u) {
  tree_t *n = (tree_t *)malloc(sizeof(tree_t));
  n->left = t, n->right = u;
  n->freq = t->freq + u->freq;
  n->str = NULL;
  return n;
}

void meld(heap_t *h) {
  for (tree_t *t = NULL, *u = NULL; h->len > 1;
       t = pop(h), u = pop(h), push(h, merge(t, u)))
    ;
}

void _print(const tree_t *t, char *str, const int d) {
  if (t->str) {
    str[d] = '\0';
    printf("%s: %s\n", t->str, str);
    return;
  }

  str[d] = '0';
  _print(t->left, str, d + 1);
  str[d] = '1';
  _print(t->right, str, d + 1);
}

void print(const tree_t *t) {
  char str[15 + 1] = {0};
  _print(t, str, 0);
}

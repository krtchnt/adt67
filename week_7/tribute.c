#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
  unsigned long data;
  bool theft;
  struct node *first_child;
  struct node *next_sibling;
} node_t;
typedef node_t tree_t;

tree_t *attach(tree_t *t, const unsigned long parent, const unsigned long child, const bool theft);
unsigned long count_paths(const tree_t *t, const unsigned long m);

node_t **nodes;

int main(void) {
  unsigned long n, m;
  tree_t *t = NULL;

  scanf("%lu %lu", &n, &m);
  nodes = (node_t **)malloc(n * sizeof(node_t *));
  unsigned long p, q;
  unsigned t_;
  t = attach(t, 0, 0, false);
  for (unsigned long _ = 0; _ < n; _++) {
    scanf("%lu %lu %u", &p, &q, &t_);
    t = attach(t, p, q, (bool)t_);
  }

  unsigned long c = count_paths(t, m);
  printf("%lu", c);
}

tree_t *attach(tree_t *t, const unsigned long parent, const unsigned long child, const bool theft) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->data = child;
  node->theft = theft;
  node->first_child = NULL;
  node->next_sibling = NULL;
  nodes[child] = node;
  if (t == NULL)
    return node;

  node_t *n = nodes[parent];
  if (n->first_child == NULL)
    n->first_child = node;
  else {
    n = n->first_child;
    while (n->next_sibling != NULL)
      n = n->next_sibling;
    n->next_sibling = node;
  }

  return t;
}

void dfs(const tree_t *t, const unsigned long m, unsigned long *c_, unsigned long *c) {
    if (t == NULL)
        return;

    if (t->theft)
        (*c_)++;

    if (*c_ <= m)
        (*c)++;

    dfs(t->first_child, m, c_, c);

    if (t->theft)
        (*c_)--;

    dfs(t->next_sibling, m, c_, c);
}

unsigned long count_paths(const tree_t *t, unsigned long m) {
    unsigned long c = 0, c_ = 0;
    dfs(t, m, &c_, &c);
    return c - 1;
}

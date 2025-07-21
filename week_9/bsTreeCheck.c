#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define __bin_tree__
#include "week9.h"

#ifndef __bin_tree__
typedef struct node {
  int data;
  struct node *left;
  struct node *right;
} node_t;

typedef node_t tree_t;
#endif

bool is_bst(tree_t *t);
bool is_avl(tree_t *t);

int main(void) {
  tree_t *t = NULL;
  int n, i;
  int parent, child;
  int branch; // 0 root, 1 left, 2 right

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d %d %d", &parent, &child, &branch);
    t = attach(t, parent, child, branch);
  }

  printf("%d %d\n", is_bst(t), is_avl(t));

  return 0;
}

bool is_bst(node_t *t) {
  node_t *i = t;
  node_t *j = NULL;

  while (i) {
    if (!i->left) {
      if (j && j->data >= i->data)
        return false;
      j = i;
      i = i->right;
    } else {
      node_t *k = i->left;
      while (k->right && k->right != i)
        k = k->right;
      if (!k->right) {
        k->right = i;
        i = i->left;
      } else {
        k->right = NULL;
        if (j && j->data >= i->data)
          return false;
        j = i;
        i = i->right;
      }
    }
  }
  return true;
}

int balance(node_t *t) {
  if (!t)
    return 0;
  int lh = balance(t->left);
  if (lh == -1)
    return -1;
  int rh = balance(t->right);
  if (rh == -1)
    return -1;
  return (abs(lh - rh) > 1) ? -1 : (lh > rh ? lh + 1 : rh + 1);
}

bool is_avl(tree_t *t) { return (balance(t) > 0) && is_bst(t); }

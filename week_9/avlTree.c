#include <stdio.h>
#include <stdlib.h>

#define __avl_tree__
#include "week9.h"

#ifndef __avl_tree__
typedef struct node {
  int data;
  int height;
  struct node *left;
  struct node *right;
} node_t;

typedef node_t avl_t;
#endif

avl_t *insert(avl_t *t, const int data);
avl_t *delete(avl_t *t, const int data);

int main(void) {
  avl_t *t = NULL;
  int n, i;
  int command, data;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &command);
    switch (command) {
    case 1:
      scanf("%d", &data);
      t = insert(t, data);
      break;
    case 2:
      scanf("%d", &data);
      t = delete (t, data);
      break;
    case 3:
      print_tree(t);
      break;
    }
  }
  return 0;
}

int height(node_t *n) { return (!n) ? 0 : n->height; }

int max(int a, int b) { return (a > b) ? a : b; }

avl_t *new(int data) {
  avl_t *t = (avl_t *)malloc(sizeof(avl_t));
  t->data = data;
  t->left = t->right = NULL;
  t->height = 1;
  return t;
}

node_t *rotate_r(node_t *y) {
  node_t *x = y->left;
  avl_t *t = x->right;

  x->right = y;
  y->left = t;

  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

node_t *rotate_l(node_t *x) {
  node_t *y = x->right;
  avl_t *t = y->left;

  y->left = x;
  x->right = t;

  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

int balance(node_t *n) { return !n ? 0 : height(n->left) - height(n->right); }

avl_t *insert(avl_t *t, const int data) {
  if (!t)
    return new (data);

  if (data < t->data)
    t->left = insert(t->left, data);
  else if (data > t->data)
    t->right = insert(t->right, data);

  t->height = 1 + max(height(t->left), height(t->right));

  int b = balance(t);
  if (b > 1 && data < t->left->data)
    return rotate_r(t);
  if (b < -1 && data > t->right->data)
    return rotate_l(t);
  if (b > 1 && data > t->left->data) {
    t->left = rotate_l(t->left);
    return rotate_r(t);
  }
  if (b < -1 && data < t->right->data) {
    t->right = rotate_r(t->right);
    return rotate_l(t);
  }
  return t;
}

node_t *_find_min(avl_t *t) {
  if (!t)
    return NULL;
  if (t->left)
    return _find_min(t->left);
  return t;
}

avl_t *delete(avl_t *t, const int data) {
  if (!t)
    return t;

  if (data < t->data)
    t->left = delete (t->left, data);
  else if (data > t->data)
    t->right = delete (t->right, data);
  else {
    if (!t->left || !t->right) {
      node_t *_t = t->left ? t->left : t->right;
      if (!_t) {
        _t = t;
        t = NULL;
      } else
        *t = *_t;
      free(_t);
    } else {
      node_t *_t = _find_min(t->right);
      t->data = _t->data;
      t->right = delete (t->right, _t->data);
    }
  }

  if (!t)
    return t;

  t->height = 1 + max(height(t->left), height(t->right));

  int b = balance(t);
  if (b > 1 && balance(t->left) >= 0)
    return rotate_r(t);
  if (b > 1 && balance(t->left) < 0) {
    t->left = rotate_l(t->left);
    return rotate_r(t);
  }
  if (b < -1 && balance(t->right) <= 0)
    return rotate_l(t);
  if (b < -1 && balance(t->right) > 0) {
    t->right = rotate_r(t->right);
    return rotate_l(t);
  }

  return t;
}

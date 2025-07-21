#include <stdio.h>
#include <stdlib.h>
#include <week8.h>
#ifndef __bin_tree__
typedef struct node {
 int data;
 struct node *left;
 struct node *right;
} node_t;
typedef node_t tree_t;
#endif

void print_preorder(tree_t *t);
void print_postorder(tree_t *t);
void print_inorder(tree_t *t);

int main(void) {
 tree_t *t = NULL;
 int n, i;
 int parent, child;
 int branch; // 0 root, 1 left, 2 right
 scanf("%d", &n);
 for (i=0; i<n; i++) {
 scanf("%d %d %d", &parent, &child,
 &branch);
 t = attach(t, parent, child, branch);
 }
 print_preorder(t);
 print_postorder(t);
 print_inorder(t);
 return 0;
}

void _print_preorder(tree_t *t) {
  if (!t) return;
  printf("%i ", t->data);
  _print_preorder(t->left);
  _print_preorder(t->right);
}

void print_preorder(tree_t *t) {
  _print_preorder(t);
  putchar('\n');
}

void _print_postorder(tree_t *t) {
  if (!t) return;
  _print_postorder(t->left);
  _print_postorder(t->right);
  printf("%i ", t->data);
}

void print_postorder(tree_t *t) {
  _print_postorder(t);
  putchar('\n');
}

void _print_inorder(tree_t *t) {
  if (!t) return;
  _print_inorder(t->left);
  printf("%i ", t->data);
  _print_inorder(t->right);
}

void print_inorder(tree_t *t) {
  _print_inorder(t);
  putchar('\n');
}

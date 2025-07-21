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

int countPathsWithSum(tree_t *t, int s);

int main(void) {
 tree_t *t = NULL;
 int n, s, i;
 int parent, child;
 int branch; // 0 root, 1 left, 2 right
 scanf("%d %d", &n, &s);
 for (i=0; i<n; i++) {
 scanf("%d %d %d", &parent, &child,
 &branch);
 t = attach(t, parent, child, branch);
 }
 printf("%d\n", countPathsWithSum(t, s));
 return 0;
}

int countPathsFromNode(tree_t *n, int s) {
    if (!n) return 0;
    int c = 0;
    if (n->data == s) c = 1;

    c += countPathsFromNode(n->left, s - n->data);
    c += countPathsFromNode(n->right, s - n->data);
    return c;
}

int countPathsWithSum(tree_t *t, int s) {
    if (!t) return 0;

    int c = countPathsFromNode(t, s);
    c += countPathsWithSum(t->left, s);
    c += countPathsWithSum(t->right, s);
    return c;
}

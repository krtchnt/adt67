#include <stdio.h>
#include <stdlib.h>
#include <week8.h>
#include <stdbool.h>
#ifndef __bin_tree__
typedef struct node {
 int data;
 struct node *left;
 struct node *right;
} node_t;
typedef node_t tree_t;
#endif

bool is_full(tree_t *t);
bool is_perfect(tree_t *t);
bool is_complete(tree_t *t);
bool is_degenerate(tree_t *t);
bool is_skewed(tree_t *t);

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
 printf("%d %d %d %d %d\n", is_full(t),
 is_perfect(t), is_complete(t),
 is_degenerate(t), is_skewed(t));
 return 0;
}

int depth(tree_t *t) {
    int d = 0;
    for (;t != NULL; t = t->left) d++;
    return d;
}

bool is_full(tree_t *t) {
    if (t == NULL) return true;
    if ((t->left == NULL && t->right != NULL) ||
        (t->left != NULL && t->right == NULL)) return false;

    return is_full(t->left) && is_full(t->right);
}

bool _is_perfect(tree_t *t, int d, int level) {
    if (t == NULL) return true;
    if (t->left == NULL && t->right == NULL) return d == level + 1;
    if (t->left == NULL || t->right == NULL) return false;

    return _is_perfect(t->left, d, level + 1) && _is_perfect(t->right, d, level + 1);
}

bool is_perfect(tree_t *t) {
    int d = depth(t);
    return _is_perfect(t, d, 0);
}

bool _is_complete(tree_t *t, int i, int node_count) {
    if (t == NULL) return true;
    if (i >= node_count) return false;
    return _is_complete(t->left, 2 * i + 1, node_count) &&
           _is_complete(t->right, 2 * i + 2, node_count);
}

int count_nodes(tree_t *t) {
    return (t == NULL) ? 0 : 1 + count_nodes(t->left) + count_nodes(t->right);
}

bool is_complete(tree_t *t) {
    int node_count = count_nodes(t);
    return _is_complete(t, 0, node_count);
}

bool is_degenerate(tree_t *t) {
    if (t == NULL) return true;
    if (t->left != NULL && t->right != NULL) return false;

    return is_degenerate(t->left) || is_degenerate(t->right);
}

bool _is_skewed_l(tree_t* t) {
    for (; t; t = t->left) if (t->right) return false;
    return true;
}

bool _is_skewed_r(tree_t* t) {
    for (; t; t = t->right) if (t->left) return false;
    return true;
}

bool is_skewed(tree_t* t) {
    if (t == NULL) return false;
    return _is_skewed_r(t) || _is_skewed_l(t);
}

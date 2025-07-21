#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *first_child;
  struct node *next_sibling;
} node_t;
typedef node_t tree_t;

typedef struct queue_node {
  node_t *data;
  struct queue_node *next;
} queue_node_t;

typedef struct queue {
  queue_node_t *front;
  queue_node_t *rear;
} queue_t;

tree_t *attach(tree_t *t, const int parent, const int child);
tree_t *detach(tree_t *t, const int node);
bool search(tree_t *t, const int node);
int degree(tree_t *t, const int node);
bool is_root(tree_t *t, const int node);
bool is_leaf(tree_t *t, const int node);
void siblings(tree_t *t, const int node);
int depth(tree_t *t, const int node);
void print_path(tree_t *t, const int start, const int end);
int path_length(tree_t *t, const int start, const int end);
void ancestor(tree_t *t, const int node);
void descendant(tree_t *t, const int node);
void bfs(tree_t *t);
void dfs(tree_t *t);
void print_tree(tree_t *t);

int main(void) {
  tree_t *t = NULL;
  int n, i, command;
  int parent, child, node, start, end;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &command);
    switch (command) {
    case 1:
      scanf("%d %d", &parent, &child);
      t = attach(t, parent, child);
      break;
    case 2:
      scanf("%d", &node);
      t = detach(t, node);
      break;
    case 3:
      scanf("%d", &node);
      printf("%d\n", search(t, node));
      break;
    case 4:
      scanf("%d", &node);
      printf("%d\n", degree(t, node));
      break;
    case 5:
      scanf("%d", &node);
      printf("%d\n", is_root(t, node));
      break;
    case 6:
      scanf("%d", &node);
      printf("%d\n", is_leaf(t, node));
      break;
    case 7:
      scanf("%d", &node);
      siblings(t, node);
      break;
    case 8:
      scanf("%d", &node);
      printf("%d\n", depth(t, node));
      break;
    case 9:
      scanf("%d %d", &start, &end);
      print_path(t, start, end);
      break;
    case 10:
      scanf("%d %d", &start, &end);
      printf("%d\n", path_length(t, start, end));
      break;
    case 11:
      scanf("%d", &node);
      ancestor(t, node);
      break;
    case 12:
      scanf("%d", &node);
      descendant(t, node);
      break;
    case 13:
      bfs(t);
      break;
    case 14:
      dfs(t);
      break;
    case 15:
      print_tree(t);
      break;
    }
  }
  return 0;
}

node_t *find(tree_t *t, const int node) {
  if (t == NULL || t->data == node)
    return t;
  node_t *n = find(t->first_child, node);
  return n == NULL ? find(t->next_sibling, node) : n;
}

void _free_node(node_t *t) {
  if (t == NULL)
    return;
  _free_node(t->first_child);
  _free_node(t->next_sibling);
  free(t);
}

void free_node(node_t *t) {
  if (t == NULL)
    return;
  _free_node(t->first_child);
  free(t);
}

tree_t *attach(tree_t *t, const int parent, const int child) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->data = child;
  node->first_child = NULL;
  node->next_sibling = NULL;
  if (t == NULL)
    return node;

  node_t *n = find(t, parent);
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

node_t *_detach(tree_t *t, const int node, node_t *_parent,
                node_t *_prev_sibling, node_t **parent, node_t **prev_sibling) {
  if (t == NULL || t->data == node) {
    *parent = _parent;
    *prev_sibling = _prev_sibling;
    return t;
  }
  node_t *n = _detach(t->first_child, node, t, NULL, parent, prev_sibling);
  return n == NULL
             ? _detach(t->next_sibling, node, _parent, t, parent, prev_sibling)
             : n;
}

tree_t *detach(tree_t *t, const int node) {
  if (t == NULL)
    return NULL;

  node_t *parent = NULL;
  node_t *prev_sibling = NULL;
  node_t *n = _detach(t, node, NULL, NULL, &parent, &prev_sibling);

  if (prev_sibling == NULL) {
    if (parent != NULL)
      parent->first_child = n->next_sibling;
  } else {
    prev_sibling->next_sibling = n->next_sibling;
  }
  free_node(n->first_child);
  free(n);
  return t;
}

bool search(tree_t *t, const int node) { return (bool)find(t, node); }

int degree(tree_t *t, const int node) {
  node_t *n = find(t, node);
  node_t *c = n->first_child;

  int d = 0;
  while (c != NULL) {
    d++;
    c = c->next_sibling;
  }

  return d;
}

bool is_root(tree_t *t, const int node) { return find(t, node) == t; }

bool is_leaf(tree_t *t, const int node) {
  return find(t, node)->first_child == NULL;
}

node_t *_siblings(tree_t *t, const int node, node_t *_parent, node_t **parent) {
  if (t == NULL || t->data == node) {
    *parent = _parent;
    return t;
  }
  node_t *n = _siblings(t->first_child, node, t, parent);
  return n == NULL ? _siblings(t->next_sibling, node, _parent, parent) : n;
}

void siblings(tree_t *t, const int node) {
  node_t *parent = NULL;
  node_t *n = _siblings(t, node, NULL, &parent);

  if (parent != NULL) {
    node_t *s = parent->first_child;

    while (s != NULL) {
      if (s->data != n->data)
        printf("%d ", s->data);
      s = s->next_sibling;
    }
  }
  putchar('\n');
}

node_t *_depth(tree_t *t, const int node, const int _c, int *c) {
  if (t == NULL || t->data == node) {
    *c = _c;
    return t;
  }
  node_t *n = _depth(t->first_child, node, _c + 1, c);
  return n == NULL ? _depth(t->next_sibling, node, _c, c) : n;
}

int depth(tree_t *t, const int node) {
  int c = 0;
  _depth(t, node, 0, &c);
  return c;
}

bool _find_path(node_t *n, node_t *n_end, node_t **p, int *len, const int c) {
  if (n == NULL)
    return false;

  if (*len < c)
    p[*len] = n;
  (*len)++;

  if (n == n_end)
    return true;
  if (_find_path(n->first_child, n_end, p, len, c))
    return true;

  (*len)--;
  if (*len < c)
    p[*len] = NULL;

  if (_find_path(n->next_sibling, n_end, p, len, c))
    return true;
  return false;
}

int find_path(tree_t *t, const int start, const int end, const bool print) {
  int len = 0;
  int c1 = 0;
  int c2 = 0;
  node_t *n_start = _depth(t, start, 0, &c1);
  node_t *n_end = _depth(t, end, 0, &c2);
  int c = c2 - c1 + 1;
  node_t **p = (node_t **)malloc(c * sizeof(node_t *));
  _find_path(n_start, n_end, p, &len, c);
  if (print) {
    for (int i = 0; i < len; i++) {
      printf("%d ", p[i]->data);
    }
    putchar('\n');
  }
  free(p);
  return len;
}

void print_path(tree_t *t, const int start, const int end) {
  find_path(t, start, end, true);
}

int path_length(tree_t *t, const int start, const int end) {
  return find_path(t, start, end, false);
}

void ancestor(tree_t *t, const int node) {
  int len = 0;
  int c2 = 0;
  node_t *n_start = t;
  node_t *n_end = _depth(t, node, 0, &c2);
  int c = c2 + 1;
  node_t **p = (node_t **)malloc(c * sizeof(node_t *));
  _find_path(n_start, n_end, p, &len, c);
  for (int i = 0; i < len; i++) {
    printf("%d ", p[i]->data);
  }
  putchar('\n');
  free(p);
}

void descendant(tree_t *t, const int node) {
  node_t *n = find(t, node);
  bfs(n);
}

void _dfs(tree_t *t) {
  if (t == NULL)
    return;
  printf("%d ", t->data);
  _dfs(t->first_child);
  _dfs(t->next_sibling);
}

void dfs(tree_t *t) {
  _dfs(t);
  putchar('\n');
}

void _print_tree(tree_t *t, const int c) {
  if (t == NULL)
    return;
  for (int _ = 0; _ < c * 4; _++)
    putchar(' ');
  printf("%d\n", t->data);
  _print_tree(t->first_child, c + 1);
  _print_tree(t->next_sibling, c);
}

void print_tree(tree_t *t) { _print_tree(t, 0); }

void enqueue(queue_t *q, tree_t *n) {
  queue_node_t *n_ = (queue_node_t *)malloc(sizeof(queue_node_t));
  n_->data = n;
  n_->next = NULL;

  if (q->rear == NULL) {
    q->front = q->rear = n_;
    return;
  }
  q->rear->next = n_;
  q->rear = n_;
}

node_t *dequeue(queue_t *q) {
  if (q->front == NULL)
    return NULL;

  queue_node_t *tmp = q->front;
  node_t *data = tmp->data;

  q->front = q->front->next;
  if (q->front == NULL)
    q->rear = NULL;

  free(tmp);
  return data;
}

int is_empty(queue_t *q) { return q->front == NULL; }

void bfs(tree_t *t) {
  if (t == NULL)
    return;

  queue_t q = {NULL, NULL};
  enqueue(&q, t);

  while (!is_empty(&q)) {
    node_t *n = dequeue(&q);
    printf("%d ", n->data);
    for (node_t *m = n->first_child; m != NULL; m = m->next_sibling)
      enqueue(&q, m);
  }
  putchar('\n');
}

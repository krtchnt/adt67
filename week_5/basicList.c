#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node_t;

node_t *append(node_t *start);
void get(node_t *start);
void show(node_t *start);
node_t *reverse(node_t *start);
node_t *cut(node_t *start);

int main(void) {
  node_t *startNode;
  int n,i;
  char command;

  startNode = NULL;
  scanf("%d", &n);
  for (i=0; i<n; i++) {
    scanf(" %c", &command);
    switch (command) {
      case 'A':
        startNode = append(startNode);
        break;
      case 'G':
        get(startNode);
        break;
      case 'S':
        show(startNode);
        break;
      case 'R':
        startNode = reverse(startNode);
        break;
      case 'C':
        startNode = cut(startNode);
        break;
      default:
        break;
    }
  }
  return 0;
}

node_t *append(node_t *start) {
  node_t *next = (node_t *)malloc(sizeof(node_t));
  scanf("%i", &next->data);
  next->next = NULL;

  if (start == NULL) {
    return next;
  }

  node_t *n = start;
  while (n->next != NULL) n = n->next;
  n->next = next;
  return start;
}

void get(node_t *start) {
  int i;
  scanf("%i", &i);

  node_t *n = start;
  for (int _ = 0; _ < i; _++) n = n->next;
  printf("%d\n", n->data);
}

void show(node_t *start) {
  node_t *n = start;
  while (n != NULL) {
    printf("%d ", n->data);
    n = n->next;
  }
  putchar('\n');
}

node_t *reverse(node_t *start) {
  node_t *prev = NULL;
  node_t *curr = start;
  node_t *next = NULL;

  while (curr != NULL) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  return prev;
}

node_t *cut(node_t *start) {
  int a, b;
  scanf("%i %i", &a, &b);

  node_t *n = start;
  for (int _ = 0; _ < a; _++) {
    node_t *m = n;
    n = n->next;
    free(m);
  }

  node_t *m = n;
  for (int _ = 0; _ < b - a; _++) m = m->next;

  node_t *l = m->next;
  m->next = NULL;
  while (l != NULL) {
    node_t *k = l;
    l = l->next;
    free(k);
  }

  return n;
}

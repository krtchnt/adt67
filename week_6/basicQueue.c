#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node_t;

typedef node_t queue_t;

queue_t *enqueue(queue_t *q, const int data);
queue_t *dequeue(queue_t *q);
void show(queue_t *q);
void empty(const queue_t *q);
void size(queue_t *q);

int main(void) {
  queue_t *q = NULL;
  int n, i, command, value;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &command);
    switch (command) {
    case 1:
      scanf("%d", &value);
      q = enqueue(q, value);
      break;
    case 2:
      q = dequeue(q);
      break;
    case 3:
      show(q);
      break;
    case 4:
      empty(q);
      break;
    case 5:
      size(q);
      break;
    }
  }
  return 0;
}

const char *EMPTY_TXT = "Queue is empty.";
const char *NONEMPTY_TXT = "Queue is not empty.";

queue_t *enqueue(queue_t *q, const int data) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->data = data;
  node->next = NULL;

  if (!q) return node;

  node_t *i = q;
  while (i->next) i = i->next;
  i->next = node;
  return q;
}

queue_t *dequeue(queue_t *q) {
  if (!q) { puts(EMPTY_TXT); return q; }
  node_t *head = q;
  node_t *next = q->next;
  printf("%d\n", head->data);
  free(head);
  return next;
}

void show(queue_t *q) {
  if (!q) { puts(EMPTY_TXT); return; }
  node_t *i = q;
  while (i) { printf("%d ", i->data); i = i->next; }
  putchar('\n');
}

void empty(const queue_t *q) { puts(q ? NONEMPTY_TXT : EMPTY_TXT); }

void size(queue_t *q) {
  node_t *i = q;
  unsigned long len = 0;
  while (i) { len++; i = i->next; }
  printf("%lu\n", len);
}

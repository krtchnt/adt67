#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node *next;
} node_t;

typedef node_t stack_t;

stack_t *push(stack_t *s, const int value);
void top(const stack_t *s);
stack_t *pop(stack_t *s);
void empty(const stack_t *s);
void size(stack_t *s);

int main(void) {
  stack_t *s = NULL;
  int n, i, command, value;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &command);
    switch (command) {
    case 1:
      scanf("%d", &value);
      s = push(s, value);
      break;
    case 2:
      top(s);
      break;
    case 3:
      s = pop(s);
      break;
    case 4:
      empty(s);
      break;
    case 5:
      size(s);
      break;
    }
  }
  return 0;
}

const char *EMPTY_TXT = "Stack is empty.";
const char *NONEMPTY_TXT = "Stack is not empty.";

stack_t *push(stack_t *s, const int value) {
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->data = value;
  node->next = NULL;

  node->next = s;
  return node;
}

void top(const stack_t *s) {
  if (!s) { puts(EMPTY_TXT); return; }
  printf("%d\n", s->data);
}

stack_t *pop(stack_t *s) {
  if (!s) return s;
  node_t *head = s;
  node_t *next = s->next;
  free(head);
  return next;
}

void empty(const stack_t *s) {
  puts(s ? NONEMPTY_TXT : EMPTY_TXT);
}

void size(stack_t *s) {
  node_t *i = s;
  unsigned long len = 0;
  while (i != NULL) { len++; i = i->next; }
  printf("%lu\n", len);
}

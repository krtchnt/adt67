#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
  unsigned short l;
  struct node *next;
} node_t;

typedef struct queue {
  node_t *head;
  node_t *tail;
  unsigned long len;
} queue_t;

queue_t new();
void enqueue(queue_t *q, const unsigned short l);
unsigned short dequeue(queue_t *q);
bool is_empty(queue_t *q);

int main(void) {
  unsigned char l;
  scanf("%hhu", &l);

  unsigned long n;
  scanf("%lu", &n);

  queue_t q_l = new();
  queue_t q_r = new();
  for (unsigned long i = 0; i < n; i++) {
    unsigned long l_i;
    char c;
    scanf("%lu %c", &l_i, &c);
    enqueue(c == 'L' ? &q_l : &q_r, l_i);
  }

  const unsigned short l_ = (unsigned short)l * 100;
  unsigned long t = 0;
  bool left = true;

  while (!is_empty(&q_l) || !is_empty(&q_r)) {
    unsigned short l_i = 0;
    queue_t *q = left ? &q_l : &q_r;
    while (!is_empty(q) && q->head->l + l_i <= l_) l_i += dequeue(q);
    left = !left;
    t++;
  }

  printf("%lu", t);
  return 0;
}

queue_t new() { const queue_t q = {NULL, NULL, 0}; return q; }

void enqueue(queue_t *q, const unsigned short l) {
  node_t *n = (node_t *)malloc(sizeof(node_t));
  n->l = l;
  n->next = NULL;

  if (is_empty(q)) {
    q->head = n;
    q->tail = n;
  } else {
    q->tail->next = n;
    q->tail = n;
  }
  q->len++;
}

unsigned short dequeue(queue_t *q) {
  const unsigned short l = q->head->l;
  q->head = q->head->next;
  q->len--;
  return l;
}

bool is_empty(queue_t *q) { return !q->len; }

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  unsigned char l;
  unsigned long i;
  struct node *next;
  struct node *prev;
} node_t;

bool has_to_drink(unsigned long c, unsigned char k) {
  if (c % k == 0)
    return true;

  while (c) {
    if (c % 10 == k)
      return true;
    c /= 10;
  }
  return false;
}

int main(void) {
  unsigned long n;
  unsigned char k;
  scanf("%lu %hhu", &n, &k);

  node_t *head = NULL;
  node_t *prev = NULL;

  for (unsigned long i = 0; i < n; i++) {
    unsigned char l;
    scanf("%hhu", &l);

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->l = l;
    new_node->i = i;
    new_node->next = NULL;
    new_node->prev = prev;

    if (prev != NULL) {
      prev->next = new_node;
    } else {
      head = new_node;
    }

    prev = new_node;
  }

  if (head != NULL) {
    head->prev = prev;
    prev->next = head;
  }

  node_t *p = head;
  unsigned long c = 1;
  unsigned long players_left = n;
  while (players_left > 1) {
    if (has_to_drink(c, k)) {
      if (p->l == 0) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);

        players_left--;
      } else
        p->l--;
    }
    p = p->next;
    c++;
  }

  printf("%lu", p->i + 1);
  return 0;
}

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DISCONNECTED 0xFF
#define UNINITIALISED 0xFE
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
  unsigned long v;
  unsigned char w;
} pair_t;

typedef struct node {
  pair_t data;
  struct node *next;
  struct node *prev;
} list_t;
typedef list_t node_t;

typedef struct {
  unsigned long v;
  list_t **adj;
} graph_t;

unsigned char **DISTANCE_CACHE = NULL;

graph_t *new_graph(const unsigned long v);
void add_edge(graph_t *g, const unsigned long u, const unsigned long v,
              const unsigned char w);
unsigned char shortest_path(const graph_t *g, const unsigned long src,
                            const unsigned long dest);

int main(void) {
  unsigned long n, m, p;
  scanf("%lu %lu %lu", &n, &m, &p);

  graph_t *g = new_graph(n);
  for (unsigned long i = 0; i < m; i++) {
    unsigned long u, v;
    unsigned char w;
    scanf("%lu %lu %hhu", &u, &v, &w);
    add_edge(g, u, v, w);
  }
  for (unsigned long i = 0; i < p; i++) {
    unsigned long s, t;
    scanf("%lu %lu", &s, &t);
    const unsigned char d = shortest_path(g, s, t);
    printf("%hhd\n", d == DISCONNECTED ? (char)-1 : (char)d);
  }
  return 0;
}

pair_t new_pair(const unsigned long v, const unsigned char w) {
  const pair_t p = {v, w};
  return p;
}

list_t *new_list(const pair_t data) {
  list_t *l = (list_t *)malloc(sizeof(list_t));
  l->data = data;
  l->next = NULL;
  return l;
}

void push_list(list_t **l, const pair_t data) {
  node_t *n = new_list(data);
  if (!*l)
    *l = n;
  else {
    node_t *c = *l;
    while (c->next)
      c = c->next;
    c->next = n;
    n->prev = c;
  }
}

typedef struct heap {
  pair_t *data;
  unsigned long len;
  unsigned long cap;
} heap_t;

heap_t *new_heap() {
  heap_t *h = (heap_t *)malloc(sizeof(heap_t));
  h->data = NULL;
  h->len = 0;
  h->cap = 0;
  return h;
}

void resize(heap_t *h) {
  if (!h->cap) {
    h->data = (pair_t *)malloc(sizeof(pair_t));
    h->cap++;
  }
  h->cap *= 2;
  h->data = (pair_t *)realloc(h->data, sizeof(pair_t) * h->cap);
}

void swp_pair(pair_t *a, pair_t *b) {
  pair_t c = *a;
  *a = *b;
  *b = c;
}

void swp_lu(unsigned long *a, unsigned long *b) {
  const unsigned long c = *a;
  *a = *b;
  *b = c;
}

void heapify_u(heap_t *h, int i) {
  int j = (i - 1) / 2;
  if (i > 0 && h->data[i].w < h->data[j].w) {
    swp_pair(&h->data[i], &h->data[j]);
    heapify_u(h, j);
  }
}

void push_heap(heap_t *h, const pair_t d) {
  if (h->len == h->cap)
    resize(h);
  h->data[h->len++] = d;
  heapify_u(h, h->len - 1);
}

void heapify_d(heap_t *h, int i) {
  int m = i, l = 2 * i + 1, r = 2 * i + 2;
  if (l < h->len && h->data[l].w < h->data[m].w)
    m = l;
  if (r < h->len && h->data[r].w < h->data[m].w)
    m = r;
  if (m != i) {
    swp_pair(&h->data[i], &h->data[m]);
    heapify_d(h, m);
  }
}

pair_t top(const heap_t *h) { return h->data[0]; }

pair_t pop(heap_t *h) {
  const pair_t t = top(h);
  h->data[0] = h->data[--h->len];
  heapify_d(h, 0);
  return t;
}

graph_t *new_graph(const unsigned long v) {
  graph_t *g = (graph_t *)malloc(sizeof(graph_t));
  g->v = v;
  g->adj = (list_t **)calloc(v, sizeof(list_t *));
  return g;
}

void add_edge(graph_t *g, const unsigned long u, const unsigned long v,
              const unsigned char w) {
  push_list(g->adj + u, new_pair(v, w));
  push_list(g->adj + v, new_pair(u, w));
}

unsigned char shortest_path(const graph_t *g, const unsigned long src,
                            const unsigned long dest) {
  if (!DISTANCE_CACHE)
    DISTANCE_CACHE = (unsigned char **)calloc(g->v, sizeof(unsigned char *));
  unsigned long src_ = src;
  unsigned long dest_ = dest;
  if (src_ > dest_)
    swp_lu(&src_, &dest_);
  if (!DISTANCE_CACHE[src_]) {
    DISTANCE_CACHE[src_] =
        (unsigned char *)malloc(g->v * sizeof(unsigned char));
    for (unsigned long i = 0; i < g->v; i++)
      DISTANCE_CACHE[src_][i] = UNINITIALISED;
  }
  if (DISTANCE_CACHE[src_][dest_] != UNINITIALISED)
    return DISTANCE_CACHE[src_][dest_];

  heap_t *h = new_heap();

  unsigned char *dist = (unsigned char *)malloc(sizeof(unsigned char) * g->v);
  for (unsigned long i = 0; i < g->v; i++)
    dist[i] = DISCONNECTED;

  push_heap(h, new_pair(src, 0));
  dist[src] = 0;

  while (h->len) {
    const unsigned char u = pop(h).v;
    for (node_t *c = g->adj[u]; c; c = c->next) {
      const unsigned long v = c->data.v;
      const unsigned long w = c->data.w;

      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        push_heap(h, new_pair(v, dist[v]));
      }
    }
  }

  DISTANCE_CACHE[src_][dest_] = dist[dest];
  return dist[dest];
}

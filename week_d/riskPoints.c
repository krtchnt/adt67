#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define UNINITIALISED 0xFFFFFFFF
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

typedef struct {
  unsigned long *data;
  unsigned long len;
  unsigned long cap;
} vec_t;

typedef struct {
  vec_t *adj;
  unsigned long v;
} graph_t;

void init_graph(graph_t *g, const unsigned long v);
void add_edge(graph_t *g, const unsigned long u, const unsigned long v);
void articulation_points(graph_t *g);
void free_graph(graph_t *g);

int main(void) {
  unsigned long n, m;
  scanf("%lu %lu", &n, &m);

  graph_t g;
  init_graph(&g, n);
  for (unsigned long i = 0; i < m; ++i) {
    unsigned long u, v;
    scanf("%lu %lu", &u, &v);
    add_edge(&g, u, v);
  }

  articulation_points(&g);
  free_graph(&g);
  return 0;
}

void init_vec(vec_t *v) {
  v->data = NULL;
  v->len = 0;
  v->cap = 0;
}

void resize_vec(vec_t *v) {
  if (!v->cap) {
    v->data = (unsigned long *)malloc(sizeof(unsigned long));
    v->cap++;
    return;
  }
  v->cap *= 2;
  v->data = (unsigned long *)realloc(v->data, sizeof(unsigned long) * v->cap);
}

void push_vec(vec_t *v, const unsigned long d) {
  if (!v)
    init_vec(v);
  if (v->len == v->cap)
    resize_vec(v);
  v->data[v->len++] = d;
}

void init_graph(graph_t *g, const unsigned long v) {
  g->v = v;
  g->adj = (vec_t *)malloc(v * sizeof(vec_t));
}

void free_graph(graph_t *g) {
  for (unsigned long i = 0; i < g->v; ++i)
    free(g->adj[i].data);
  free(g->adj);
}

void add_edge(graph_t *g, const unsigned long u, const unsigned long v) {
  push_vec(g->adj + u, v);
  push_vec(g->adj + v, u);
}

void _articulation_points(graph_t *g, const unsigned long u, bool *visited,
                          unsigned long *disc, unsigned long *low,
                          unsigned long *time, const unsigned long parent,
                          bool *is_ap) {
  unsigned long children = 0;
  visited[u] = true;
  disc[u] = low[u] = ++*time;
  for (unsigned long i = 0; i < g->adj[u].len; i++) {
    unsigned long v = g->adj[u].data[i];
    if (!visited[v]) {
      children++;
      _articulation_points(g, v, visited, disc, low, time, u, is_ap);

      low[u] = MIN(low[u], low[v]);

      if (parent != UNINITIALISED && low[v] >= disc[u])
        is_ap[u] = true;
    } else if (v != parent)
      low[u] = MIN(low[u], disc[v]);
  }
  if (parent == UNINITIALISED && children > 1)
    is_ap[u] = true;
}

void articulation_points(graph_t *g) {
  unsigned long *disc = (unsigned long *)calloc(g->v, sizeof(unsigned long));
  unsigned long *low = (unsigned long *)malloc(sizeof(unsigned long) * g->v);
  bool *visited = (bool *)calloc(g->v, sizeof(bool));
  bool *is_ap = (bool *)calloc(g->v, sizeof(bool));
  unsigned long time = 0, par = UNINITIALISED;

  for (unsigned long i = 0; i < g->v; ++i)
    if (!visited[i])
      _articulation_points(g, i, visited, disc, low, &time, par, is_ap);

  for (unsigned long i = 0; i < g->v; ++i)
    if (is_ap[i])
      printf("%lu ", i);
  putchar('\n');
  free(disc);
  free(low);
  free(visited);
  free(is_ap);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNINITIALISED 0xFFFFFFFF
#define DELETED 0xFFFFFFFE
#define LOAD_FACTOR_THRESHOLD 0.7

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

typedef struct {
  unsigned long len;
  unsigned long cap;
  unsigned long *data;
} set_t;

typedef struct {
  unsigned long k;
  set_t v;
} pair_t;

typedef struct {
  unsigned long len;
  unsigned long cap;
  pair_t *data;
} map_t;

typedef struct {
  set_t *data;
  unsigned long len;
  unsigned long cap;
} vec_t;

void init_map(map_t *m);
void push_map(map_t *m, const pair_t p);
void init_set(set_t *s);
void push_set(set_t *s, const unsigned long d);
void bron_kerbosch(set_t *r, set_t *p, set_t *x, map_t *g, vec_t *c);
void init_vec(vec_t *v);
set_t *get_map(const map_t *m, const unsigned long k);

int main(void) {
  unsigned long n, m;
  scanf("%lu %lu", &n, &m);

  map_t g;
  init_map(&g);
  for (unsigned long i = 0; i < m; i++) {
    unsigned long u, v;
    scanf("%lu %lu", &u, &v);

    set_t *pv1 = get_map(&g, u);
    if (pv1) {
      push_set(pv1, v);
    } else {
      pair_t p;
      p.k = u;
      init_set(&p.v);
      push_set(&p.v, v);
      push_map(&g, p);
    }

    set_t *pv2 = get_map(&g, v);
    if (pv2) {
      push_set(pv2, u);
    } else {
      pair_t p;
      p.k = v;
      init_set(&p.v);
      push_set(&p.v, u);
      push_map(&g, p);
    }
  }

  set_t vs;
  init_set(&vs);
  for (unsigned long i = 0; i < g.cap; i++) {
    if (g.data[i].k == UNINITIALISED)
      continue;
    push_set(&vs, g.data[i].k);
  }

  vec_t cs;
  init_vec(&cs);
  set_t r, x;
  init_set(&r);
  init_set(&x);

  bron_kerbosch(&r, &vs, &x, &g, &cs);

  unsigned long max = 0;
  for (unsigned long i = 0; i < cs.len; i++)
    max = MAX(max, cs.data[i].len);
  printf("%lu\n", max);
  return 0;
}

void init_set(set_t *s) {
  s->len = 0;
  s->cap = 0;
  s->data = NULL;
}

set_t *new_set() {
  set_t *s = (set_t *)malloc(sizeof(set_t));
  init_set(s);
  return s;
}

unsigned long hash(const unsigned long d, const unsigned long cap) {
  unsigned long prime = 1;
  return (d * prime) & (cap - 1);
}

void push_set(set_t *s, const unsigned long d);
void resize_set(set_t *s) {
  unsigned long cap = s->cap;
  unsigned long cap_ = cap ? cap * 2 : 1;
  unsigned long *data = s->data;
  s->data = (unsigned long *)malloc(cap_ * sizeof(unsigned long));

  for (unsigned long i = 0; i < cap_; i++)
    s->data[i] = UNINITIALISED;

  s->cap = cap_;
  s->len = 0;

  for (unsigned long i = 0; i < cap; i++) {
    if (data[i] != UNINITIALISED && data[i] != DELETED) {
      push_set(s, data[i]);
    }
  }

  free(data);
}

void push_set(set_t *s, const unsigned long d) {
  if (!s->cap || (double)s->len / (double)s->cap >= LOAD_FACTOR_THRESHOLD)
    resize_set(s);

  unsigned long idx = hash(d, s->cap);
  const unsigned long start_idx = idx;
  unsigned long n = s->cap - 1;
  unsigned long _idx = UNINITIALISED;

  for (unsigned long i = 0; i < s->cap; i++) {
    idx = (start_idx + (i * i + i) / 2) & n;

    if (s->data[idx] == d)
      return;

    if (s->data[idx] == DELETED && _idx == UNINITIALISED) {
      _idx = idx;
    }

    if (s->data[idx] == UNINITIALISED) {
      if (_idx != UNINITIALISED)
        idx = _idx;
      s->data[idx] = d;
      s->len++;
      return;
    }
  }

  resize_set(s);
  push_set(s, d);
}

unsigned long find_set(const set_t *s, const unsigned long d) {
  if (!s->cap)
    return UNINITIALISED;
  unsigned long idx = hash(d, s->cap);
  const unsigned long start_idx = idx;
  unsigned long n = s->cap - 1;
  for (unsigned long i = 0; i < s->cap; ++i) {
    idx = (start_idx + (i * i + i) / 2) & n;

    if (s->data[idx] == UNINITIALISED)
      return UNINITIALISED;
    if (s->data[idx] == d)
      return idx;
  }
  return UNINITIALISED;
}

void remove_set(set_t *s, const unsigned long d) {
  for (unsigned long i = 0; i < s->cap; ++i) {
    if (s->data[i] == d) {
      s->data[i] = DELETED;
      s->len--;
      return;
    }
  }
}

unsigned long first_set(const set_t *s) {
  unsigned long i = 0;
  while (i < s->cap && (s->data[i] == UNINITIALISED || s->data[i] == DELETED))
    i++;
  return s->data[i];
}

void swp_set(set_t **a, set_t **b) {
  set_t *c = *a;
  *a = *b;
  *b = c;
}

void intersect_set(set_t *a, set_t *b, set_t *c) {
  init_set(c);

  for (unsigned long i = 0; i < a->cap; i++) {
    const unsigned long x = a->data[i];
    if (x == UNINITIALISED)
      continue;
    if (find_set(b, x) != UNINITIALISED) {
      push_set(c, x);
    }
  }
}

set_t *memcpy_set(const set_t *s) {
  set_t *s_ = (set_t *)malloc(sizeof(set_t));
  s_->len = s->len;
  s_->cap = s->cap;

  if (s->data) {
    s_->data = (unsigned long *)malloc(s_->cap * sizeof(unsigned long));
    memcpy(s_->data, s->data, s_->cap * sizeof(unsigned long));
  } else {
    s_->data = NULL;
  }
  return s_;
}

void init_vec(vec_t *v) {
  v->data = NULL;
  v->len = 0;
  v->cap = 0;
}

void resize_vec(vec_t *v) {
  if (!v->cap) {
    v->data = (set_t *)malloc(sizeof(set_t));
    v->cap++;
    return;
  }
  v->cap *= 2;
  v->data = (set_t *)realloc(v->data, sizeof(set_t) * v->cap);
}

void push_vec(vec_t *v, set_t d) {
  if (v->len == v->cap)
    resize_vec(v);
  v->data[v->len++] = d;
}

void init_map(map_t *m) {
  m->len = 0;
  m->cap = 0;
  m->data = NULL;
}

set_t *get_map(const map_t *m, const unsigned long d) {
  if (!m->cap)
    return NULL;
  unsigned long idx = hash(d, m->cap);
  const unsigned long start_idx = idx;
  unsigned long n = m->cap - 1;
  for (unsigned long i = 0; i < m->cap; ++i) {
    idx = (start_idx + (i * i + i) / 2) & n;

    if (m->data[idx].k == UNINITIALISED)
      return NULL;
    if (m->data[idx].k == d) {
      return &m->data[idx].v;
    };
  }
  return NULL;
}

void push_map(map_t *m, const pair_t p);
void resize_map(map_t *m) {
  unsigned long cap = m->cap;
  unsigned long cap_ = cap ? cap * 2 : 1;
  pair_t *data = m->data;
  m->data = (pair_t *)malloc(cap_ * sizeof(pair_t));

  for (unsigned long i = 0; i < cap_; i++)
    m->data[i].k = UNINITIALISED;

  m->cap = cap_;
  m->len = 0;

  for (unsigned long i = 0; i < cap; i++)
    if (data[i].k != UNINITIALISED)
      push_map(m, data[i]);
  free(data);
}

void push_map(map_t *m, const pair_t p) {
  if (!m->cap || (double)m->len / (double)m->cap >= LOAD_FACTOR_THRESHOLD)
    resize_map(m);

  unsigned long idx = hash(p.k, m->cap);
  const unsigned long start_idx = idx;
  unsigned long n = m->cap - 1;

  for (unsigned long i = 0; i < m->cap; i++) {
    idx = (start_idx + (i * i + i) / 2) & n;

    if (m->data[idx].k == UNINITIALISED) {
      m->data[idx].k = p.k;
      m->data[idx].v = p.v;
      m->len++;
      return;
    }

    if (m->data[idx].k == p.k) {
      m->data[idx].v = p.v;
      return;
    }
  }
}

void bron_kerbosch(set_t *r, set_t *p, set_t *x, map_t *g, vec_t *c) {
  if (!p->len && !x->len) {
    push_vec(c, *r);
    return;
  }

  while (p->len) {
    unsigned long v = first_set(p);
    set_t *r_ = memcpy_set(r);
    push_set(r_, v);

    set_t *adj = get_map(g, v);
    set_t p_, x_;
    intersect_set(p, adj, &p_);
    intersect_set(x, adj, &x_);

    bron_kerbosch(r_, memcpy_set(&p_), memcpy_set(&x_), g, c);

    remove_set(p, v);
    push_set(x, v);
  }
}

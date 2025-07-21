#include <stdio.h>
#include <stdlib.h>

typedef struct sushi {
  unsigned long price;
  unsigned long weight;
  unsigned long index;
  double value;
} sushi_t;

void lis(sushi_t **x, const unsigned long n);

int main() {
  unsigned long n;
  scanf("%lu", &n);
  sushi_t **belt = (sushi_t **)malloc(n * sizeof(sushi_t *));
  for (unsigned long i = 0; i < n; i++) {
    unsigned long p, w;
    scanf("%lu %lu", &p, &w);
    belt[i] = (sushi_t *)malloc(sizeof(sushi_t));
    belt[i]->price = p;
    belt[i]->weight = w;
    belt[i]->index = i;
    belt[i]->value = (double)w / (double)p;
  }

  lis(belt, n);

  for (unsigned long i = 0; i < n; i++)
    free(belt[i]);
  free(belt);
  return 0;
}

void lis(sushi_t **x, const unsigned long n) {
  long *p = (long *)malloc(n * sizeof(long));
  long *m = (long *)malloc((n + 1) * sizeof(long));
  m[0] = -1;

  long l = 0;

  for (long i = 0; i < n; i++) {
    long lo = 1;
    long hi = l + 1;

    while (lo < hi) {
      long mid = lo + (hi - lo) / 2;
      if (x[m[mid]]->value > x[i]->value) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }

    long l_ = lo;

    p[i] = m[l_ - 1];
    m[l_] = i;

    if (l_ > l) {
      l = l_;
    }
  }

  sushi_t **s = (sushi_t **)malloc(l * sizeof(sushi_t *));
  long k = m[l];

  for (long j = l - 1; j >= 0; j--) {
    s[j] = x[k];
    k = p[k];
  }

  char *b = (char *)malloc((n + 1) * sizeof(char));
  for (unsigned long bi = 0; bi < n + 1; bi++)
    b[bi] = '0';

  unsigned long total_price = 0;
  for (unsigned long j = 0; j < l; j++) {
    b[s[j]->index] = '1';
    total_price += s[j]->price;
  }

  for (unsigned long j = 0; j < n; j++) {
    putchar(b[j]);
    putchar(' ');
  }
  putchar('\n');

  printf("%lu\n", total_price);

  free(b);
  free(p);
  free(m);
  free(s);
}

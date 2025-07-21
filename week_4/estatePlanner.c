// O(min(m,n))

#include <stdio.h>
#include <math.h>

#define MIX(x, y) (((x) < (y)) ? (x) : (y))

unsigned long get_partitions(const unsigned long m, const unsigned long n) {
  if (!m || !n) return 0;

  const unsigned long a = (unsigned long)exp2(floor(log2((double)MIX(m, n))));
  return 1 + get_partitions(a, n - a) + get_partitions(m - a, n);
}

int main(void) {
  unsigned long m, n;
  scanf("%lu %lu", &m, &n);

  unsigned long partitions = get_partitions(m, n);
  printf("%lu", partitions);
}

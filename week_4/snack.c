// O(m)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define K 100

// O(m+k) = O(m+100) = O(m)
void counting_sort(unsigned char *input, const unsigned long n) {
  unsigned char count[K + 1] = {0};
  unsigned char *output = (unsigned char*)malloc(n * sizeof(unsigned char));

  for (unsigned long i = 0; i < n; i++) count[input[i]]++;
  for (unsigned char i = 1; i <= K; i++) count[i] += count[i - 1];
  for (signed long i = n - 1; i >= 0; i--) {
    unsigned char j = input[i];
    count[j]--;
    output[count[j]] = input[i];
  }

  memcpy(input, output, n * sizeof(unsigned char));
  free(output);
}

unsigned long calculate_snack_n(
    const unsigned char *snacks,
    const unsigned long m,
    const unsigned long v
) {
  unsigned long snack_n = 0;
  unsigned long remaining = v;

  for (signed long i = m - 1; i >= 0; i--) {
    snack_n += remaining / snacks[i];
    remaining %= snacks[i];
  }

  return snack_n;
}

int main(void) {
  unsigned long m, v;
  scanf("%lu", &m);

  unsigned char *snacks = (unsigned char*)malloc(m * sizeof(unsigned char));
  for (unsigned long i = 0; i < m; i++) scanf("%hhu", snacks + i);
  counting_sort(snacks, m);

  scanf("%lu", &v);

  const unsigned long snack_n = calculate_snack_n(snacks, m, v);
  printf("%lu", snack_n);
  free(snacks);
  return 0;
}

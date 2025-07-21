// O(sqrt(n))

#include <stdio.h>
#include <stdbool.h>

bool is_prime(const unsigned long long n) {
  unsigned char fs = 0;
  unsigned long long f = 2;

  while (f*f <= n) {
    if (n % f == 0) { fs++; n /= f; continue; }
    f++;
  }
  if (n != 1) fs++;
  return fs == 1;
}

int main(void) {
  unsigned long long n;
  scanf("%llu", &n);

  const bool n_is_prime = is_prime(n);
  printf("%u", n_is_prime);
}

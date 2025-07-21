#include <stdio.h>

unsigned long long* euclids_formula(const unsigned short m, const unsigned short n) {
  static unsigned long long triple[3];

  const unsigned long m_squared = (unsigned long)m * (unsigned long)m;
  const unsigned long n_squared = (unsigned long)n * (unsigned long)n;

  const unsigned long long m_squared_llu = (unsigned long long)m_squared;
  const unsigned long long n_squared_llu = (unsigned long long)n_squared;

  triple[0] = m_squared_llu - n_squared_llu;
  triple[1] = (unsigned long long)m * (unsigned long long)n * (unsigned long long)2;
  triple[2] = m_squared_llu + n_squared_llu;

  return triple;
}

int main(void) {
  unsigned short m, n;

  scanf("%hu %hu", &m, &n);

  const unsigned long long* pythagorean_triple = euclids_formula(m, n);
  printf("%llu %llu %llu\n", pythagorean_triple[0], pythagorean_triple[1], pythagorean_triple[2]);
  return 0;
}

#include <stdio.h>
#include <math.h>

unsigned char lucas_lehmer(const unsigned char p) {
  unsigned char s = 4;
  unsigned char m = pow(2, p) - 1;
  for (unsigned char _; _ < p - 2; _++)
    s = ((s * s) - 2) % m;
  return s == 0;
}

unsigned short perfect(unsigned char p) {
  if (p > 2) {
    if (!(p % 2)) p--;
    while (!lucas_lehmer(p)) p -= 2;
  }

  return pow(2, p-1) * (pow(2, p) - 1);
}

int main(void) {
  unsigned long m;

  scanf("%lu", &m);

  unsigned char p = (unsigned char)(log2(sqrt((double)m * 8. + 1.) + 1.) - 1.);

  if (p < 2)
    putchar('1');
  else {
    unsigned short n = perfect(p);
    printf("%hu", n);
  }
}

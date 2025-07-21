#include <stdio.h>

int main(void) {
  unsigned char n;

  scanf("%hhu", &n);

  for (unsigned char i = 1; i <= n; i++) {
    unsigned char indent = (n - i) * 3;
    for (unsigned char _ = 0; _ < indent; _++)
      putchar(' ');

    unsigned long coefficient = 1;
    for (unsigned char j = 1; j <= i; j++) {
      printf("%6lu", coefficient);
      coefficient = coefficient * (i - j) / j;
    }
    putchar('\n');
  }
}

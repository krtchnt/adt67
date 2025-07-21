#include <stdio.h>

unsigned char calculate_ascii_difference(const char first, const char second) {
  if (first > second) {
    return first - second;
  }
  return second - first;
}

int main(void) {
  char first, second;

  scanf("%c %c", &first, &second);
  const unsigned char ascii_difference = calculate_ascii_difference(first, second);

  printf("%d\n", ascii_difference);
  return 0;
}

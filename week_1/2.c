#include <stdio.h>

#define SECONDS_PER_SQUARE_METRES 5.3819555528

double calculate_mowing_duration(const unsigned short length, const unsigned short width) {
  const unsigned long area = (unsigned long)length * (unsigned long)width;
  return (double)area * SECONDS_PER_SQUARE_METRES;
}

int main(void) {
  unsigned short length, width;

  printf("length(m.): ");
  scanf("%hu", &length);

  printf("width(m.): ");
  scanf("%hu", &width);

  const double mowing_duration = calculate_mowing_duration(length, width);

  printf("Use %.5f seconds.\n", mowing_duration);
  return 0;
}

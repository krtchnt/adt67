#include <stdio.h>

float calculate_trapezoid_area(const unsigned short base_1, const unsigned short base_2, const unsigned short height) {
  float m = ((float)base_1 + (float)base_2) / 2.0;
  return m * (float)height;
}

int main(void) {
  unsigned short a, b, h;
  printf("a: ");
  scanf("%d", &a);
  printf("b: ");
  scanf("%d", &b);
  printf("h: ");
  scanf("%d", &h);

  const float trapezoid_area = calculate_trapezoid_area(a, b, h);
  printf("Area is %.1f\n", trapezoid_area);
  return 0;
}

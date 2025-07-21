#include <stdio.h>
#include <math.h>

double calculate_trapezoid_area(
    const double base_1,
    const double base_2,
    const double height
) {
  double m = (base_1 + base_2) / 2.0;
  return m * height;
}

double integrand(
    const double a_upper,
    const double b_upper,
    const double x
) {
  return a_upper * sin((M_PI * x) / b_upper);
}

double calculate_definite_integral(
    const double a,
    const double b,
    const double a_upper,
    const double b_upper,
    const unsigned short n
) {
  const double dx = (b - a) / (double)n;
  double value = 0;

  double x_s[n + 1];
  x_s[0] = a;
  for (unsigned short i = 1; i <= n; i++) {
    x_s[i] = a + ((double)i * dx);

    const double x_1 = x_s[i-1];
    const double x_2 = x_s[i];

    const double f_x_1 = integrand(a_upper, b_upper, x_1);
    const double f_x_2 = integrand(a_upper, b_upper, x_2);

    const double partial_value = calculate_trapezoid_area(f_x_1, f_x_2, dx);
    value += partial_value;
  }

  return value;
}

int main(void) {
  double a, b, a_upper, b_upper;
  unsigned short n;

  scanf("%lf %lf %lf %lf %hu", &a, &b, &a_upper, &b_upper, &n);

  double definite_integral = calculate_definite_integral(a, b, a_upper, b_upper, n);
  printf("%.5f", definite_integral);
}

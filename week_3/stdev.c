#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_mean(const signed char* xs, const unsigned long n) {
  signed long long sum = 0;
  for (unsigned long i = 0; i < n; i++)
    sum += (signed long long)xs[i];

  return (double)sum / (double)n;
}

double calculate_standard_deviation(const signed char* xs, const unsigned long n) {
  const double mean = calculate_mean(xs, n);

  double sum = 0.;
  for (unsigned long i = 0; i < n; i++)
    sum += pow((double)xs[i] - mean, 2.);

  return sqrt(sum / (double)n);
}

int main(void) {
  unsigned long n;
  scanf("%lu", &n);

  signed char* xs = (signed char*)calloc(n, sizeof(signed char));
  for (unsigned long i = 0; i < n; i++)
    scanf("%hhi", xs + i);

  const double sd = calculate_standard_deviation(xs, n);
  printf("%.2f", sd);
  return 0;
}

#include <stdio.h>

float calculate_bmi(const unsigned short weight, const unsigned short height) {
  const float height_m = (float)height / 100.0;
  return (float)weight / (height_m * height_m);
}

int main(void) {
  unsigned short weight, height;

  scanf("%hu %hu", &weight, &height);

  const float bmi = calculate_bmi(weight, height);

  char* evaluation;

  if (bmi < 18.6)
    evaluation = "underweight";
  else if (bmi < 25)
    evaluation = "healthy";
  else if (bmi < 30)
    evaluation = "overweight";
  else
    evaluation = "obese";

  printf("BMI: %.4f and you are %s\n", bmi, evaluation);
  return 0;
}

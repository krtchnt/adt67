#include <stdio.h>
#include <math.h>

typedef struct student {
  char name[30 + 1];
  unsigned char score;
} student_t;

void inputStudent(student_t *students, const int n);
void showStudentGrade(const student_t *students, const int n);

int main(void) {
  student_t students[1000];
  int n;
  scanf("%d", &n);
  inputStudent(students, n);
  showStudentGrade(students, n);
  return 0;
}

double mean;
double standard_deviation;
double mean_add_standard_deviation;
double mean_sub_standard_deviation;
double mean_add_1_5_standard_deviation;
double mean_sub_1_5_standard_deviation;

void calculate_mean(const student_t *student_t, const int n) {
  unsigned long sum = 0;
  for (int i = 0; i < n; i++) sum += student_t[i].score;

  mean = (double)sum / (double)n;
}

void calculate_standard_deviation(const student_t *students, const int n) {
  double sum = 0;
  for (int i = 0; i < n; i++) sum += pow((double)(students[i].score) - mean, 2);

  standard_deviation = sqrt(sum / ((double)n - 1.));
}

void calculate_required_values() {
  const double standard_deviation_1_5 = 1.5 * standard_deviation;
  mean_add_standard_deviation = mean + standard_deviation;
  mean_sub_standard_deviation = mean - standard_deviation;
  mean_add_1_5_standard_deviation = mean + standard_deviation_1_5;
  mean_sub_1_5_standard_deviation = mean - standard_deviation_1_5;
}

char calculate_grade(const unsigned char score) {
  char grade;
  if      (mean_add_1_5_standard_deviation <= score                                            ) grade = 'A';
  else if (mean_add_1_5_standard_deviation >  score && score >= mean_add_standard_deviation    ) grade = 'B';
  else if (    mean_add_standard_deviation >  score && score >= mean_sub_standard_deviation    ) grade = 'C';
  else if (    mean_sub_standard_deviation >  score && score >= mean_sub_1_5_standard_deviation) grade = 'D';
  else                                                                                           grade = 'F';

  return grade;
}

void inputStudent(student_t *students, const int n) {
  for (int i = 0; i < n; i++) scanf("%s %hhu", students[i].name, &students[i].score);
}

void showStudentGrade(const student_t *students, const int n) {
  calculate_mean(students, n);
  calculate_standard_deviation(students, n);
  calculate_required_values();

  for (int i = 0; i < n; i++) {
    const char grade = calculate_grade(students[i].score);
    fputs(students[i].name, stdout);
    putchar(' ');
    putchar(grade);
    putchar('\n');
  }
}

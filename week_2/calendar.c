#include <stdio.h>

const char* get_month_name(const unsigned char month);
void print_calendar(const unsigned short year, const unsigned char month);
const unsigned char get_days_in_month(const unsigned char month, const unsigned char is_leap_year);
const unsigned char is_leap_year(const unsigned short year);

int main(void) {
  unsigned short year;
  unsigned char month;

  printf("Enter year: ");
  scanf("%hu", &year);
  printf("Enter month: ");
  scanf("%hhu", &month);

  printf("====================\n");
  print_calendar(year, month);
}

void print_calendar(const unsigned short year, const unsigned char month) {
  const char* month_name = get_month_name(month);

  printf("%s %hu\n", month_name, year);
  printf("Sun Mon Tue Wed Thu Fri Sat\n");

  unsigned short current_year = 1990;
  unsigned char current_month = 1;
  unsigned char current_day_of_week = 1;
  unsigned char current_year_is_leap_year = is_leap_year(current_year);
  unsigned char current_days_in_month = get_days_in_month(current_month, current_year_is_leap_year);

  while (current_year != year || current_month != month) {
    if (++current_month == 13) {
      current_month = 1;
      current_year_is_leap_year = is_leap_year(++current_year);
    }
    current_day_of_week = (current_day_of_week + current_days_in_month) % 7;
    current_days_in_month = get_days_in_month(current_month, current_year_is_leap_year);
  }

  unsigned char current_date = 1;
  for (unsigned char _ = 0; _ < 4 * current_day_of_week; _++)
    putchar(' ');
  while (current_date <= current_days_in_month) {
    printf("%3hhu ", current_date++);
    if (++current_day_of_week == 7) {
      current_day_of_week = 0;
      putchar('\n');
    }
  }
}

const unsigned char get_days_in_month(const unsigned char month, const unsigned char is_leap_year) {
  unsigned char days;

  switch (month) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
      days = 31;
      break;
    case 4: case 6: case 9: case 11:
      days = 30;
      break;
    case 2:
      days = is_leap_year ? 29 : 28;
      break;
  }

  return days;
}

const unsigned char is_leap_year(const unsigned short year) {
  return (!(year % 4) && (year & 100)) || !(year % 400);
}

const char* get_month_name(const unsigned char month) {
  char* month_name;

  switch (month) {
    case 1:
      month_name = "January";
      break;
    case 2:
      month_name = "February";
      break;
    case 3:
      month_name = "March";
      break;
    case 4:
      month_name = "April";
      break;
    case 5:
      month_name = "May";
      break;
    case 6:
      month_name = "June";
      break;
    case 7:
      month_name = "July";
      break;
    case 8:
      month_name = "August";
      break;
    case 9:
      month_name = "September";
      break;
    case 10:
      month_name = "October";
      break;
    case 11:
      month_name = "November";
      break;
    case 12:
      month_name = "December";
      break;
  }

  return month_name;
}

/* Rewrite the routine day_of_year and month_day with pointers
 * instead of indexing */
#include <stdio.h>

static char nonleap[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char leap[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static char *daytab[] = {
  nonleap,
  leap
};

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
  int err, month, day;

  printf("day_of_year(2016, 3, 16) = %d, expected %d\n", day_of_year(2016, 3, 16), 76);
  printf("day_of_year(2018, 3, 16) = %d, expected %d\n", day_of_year(2018, 3, 16), 75);
  printf("day_of_year(2018, 13, 16) = %d, expected %d\n", day_of_year(2018, 13, 16), -1);
  printf("day_of_year(2018, 2, 29) = %d, expected %d\n", day_of_year(2018, 2, 29), -2);

  err = month_day(2016, 76, &month, &day);
  printf("month_day(2016, 75, m, d) = %d %d, expected %d %d\n", month, day, 3, 16);
  err = month_day(2018, 76, &month, &day);
  printf("month_day(2018, 75, m, d) = %d %d, expected %d %d\n", month, day, 3, 17);
  err = month_day(2018, 366, &month, &day);
  printf("month_day(2018, 366, m, d) = %d, expected %d\n", err, -2);
  err = month_day(2018, 365, &month, &day);
  printf("month_day(2018, 365, m, d) = %d %d, expected %d %d\n", month, day, 12, 31);
  err = month_day(2016, 365, &month, &day);
  printf("month_day(2018, 365, m, d) = %d, expected %d\n", err, -2);
}

/* day_of_year: set day of year from month and day */
int day_of_year(int year, int month, int day)
{
  if (month < 1 || month > 12 || year < 0)
    return -1;

  int i, leap;

  leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
  if (day > *(daytab[leap] + month))
    return -2;
  for (i = 1; i < month; i++)
    day += *(daytab[leap] + i);
  return day;
}

/* month_day: set month, day from day of year */
int month_day(int year, int yearday, int *pmonth, int *pday)
{
  int i, leap;

  if (year < 0)
    return -1;

  leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
  if ((leap && (yearday > 364)) || yearday > 365)
    return -2;
  for (i = 1; yearday > *(daytab[leap] + i); i++)
    yearday -= *(daytab[leap] + i);
  *pmonth = i;
  *pday = yearday;
  return 0;
}

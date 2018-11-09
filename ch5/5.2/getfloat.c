#include <ctype.h>
#include <stdio.h>
#include "getch.h"

int get_float(double *);

int main()
{
  int n, c;
  double array[100];

  for (n = 0; n < 100 && c != EOF;) {
    c = get_float(&array[n]);
    if (c != 0)
      n++;
  }

  for (int j = 0; j < n; j++)
    printf("%f\n", array[j]);
}

int get_float(double *pn)
{
  double power;
  int c, sign;

  while (isspace(c = getch()))
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  if (!isdigit(c) && c != EOF) {
    ungetch(c);
    return 0;
  }

  for (*pn = 0.0; isdigit(c); c = getch())
    *pn = 10.0 * *pn + (c - '0');

  if (c == '.')
    c = getch();

  for (power = 1.0; isdigit(c); c = getch()) {
    *pn = 10.0 * *pn + (c - '0');
    power *= 10.0;
  }

  *pn = sign * (*pn / power);

  if (c != EOF)
    ungetch(c);
  return c;
}

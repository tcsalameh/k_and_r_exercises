#include <ctype.h>
#include <stdio.h>
#include "getch.h"

int getch(void);
void ungetch(int);
int getint(int *);

int main()
{
  int i, n, array[100];

  i = 0;
  for (n = 0; n < 100 && getint(&array[n]) != EOF; n++)
    i++;

  for (i; i >= 0; i--)
    printf("%d\n", array[i]);
}

int getint(int *pn)
{
  int c, sign;

  while (isspace(c = getch()))
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); /* not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

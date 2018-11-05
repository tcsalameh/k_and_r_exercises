/* As written, getint treats a + or - not followed
 * by a digit as a valid representation of zero.
 * Fix it to push such a character back on the input. */
#include <ctype.h>
#include <stdio.h>
#include "getch.h"

int getch(void);
void ungetch(int);
int getint(int *);

int main()
{
  int n, c, array[100];

  for (n = 0; n < 100 && c != EOF;) {
    c = getint(&array[n]);
    if (c != 0)
      n++;
  }

  for (int j = 0; j < n; j++)
    printf("%d\n", array[j]);
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
  if (!isdigit(c) && c != EOF) {
    ungetch(c);
    return 0;
  }
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

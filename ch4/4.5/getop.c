#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop: get next operator or numeric operand */
int getop(char s[])
{
  int i, c;

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (c >= 'a' && c <= 'z') {
    s[0] = c;
    return VARIABLE;
  }
  if (!isdigit(c) && c != '.' && c != '-')
    return c;

  if (c == '-') {
    if (isdigit(c = getch())) {
      ungetch(c);
      c = '-';
    } else {
      ungetch(c);
      return '-';
    }
  }

  i = 0;
  if (isdigit(c) || c == '-')
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

/* Write a version of itoa that accepts three arguments
 * instead of two. The third argument is a minimum field
 * width; the converted number must be padded with blanks
 * on the left if necessary to make it wide enough */
#include <stdio.h>
#include <limits.h>
#include "reverse.h"

void itoa(int n, char s[], int width);

int main()
{
  char s[20];
  int tests[] = {0, 1, -5, -523, -2147483648, 3948210};
  char expected[][20] = {
    "   0",
    "   1",
    "  -5",
    "-523",
    "-2147483648",
    "3948210"
  };

  for (int i=0; i<6; i++) {
    itoa(tests[i], s, 4);
    if (strcmp(s, expected[i]))
      printf("Expected %s for itoa(%d, s, 4); got %s.\n", expected[i], tests[i], s);
  }
}

void itoa(int n, char s[], int width)
{
  int sign;
  int i = 0;
  int overflow = 0;

  if (n == INT_MIN) {
    n += 1;
    overflow = 1;
  }

  if ((sign = n) < 0)  /* record sign */
    n = -n;            /* make n positive */

  do {        /* generate digits in reverse order */
    if (overflow) {
      s[i++] = n % 10 + '1';
      overflow = 0;
    } else {
      s[i++] = n % 10 + '0';
    }
  } while ((n /= 10) > 0);

  if (sign < 0)
    s[i++] = '-';

  while (i < width)
    s[i++] = ' ';

  s[i] = '\0';
  reverse(s);
}

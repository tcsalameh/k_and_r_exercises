/* Write the function itob(n, s, b) that converts
 * the integer into a base b character representation
 * in the string s. In particular, itob(n, s, 16) formats
 * n as a hexadecimal integer in s. */
#include <stdio.h>
#include <limits.h>
#include "reverse.h"

#define DIGITS "0123456789abcdefghijklmnopqrstuvwxyz"
#define MAX_BASE 35    /* Max representable base */

int itob(int n, char s[], int b);
int handle_overflow(char s[], int i, int n, int b);

int main()
{
  char s[20];

  int tests[] = {0, 1, -35, 23495, -2147483648};
  char hex_expected[][20] = {
    "0",
    "1",
    "-23",
    "5bc7",
    "-80000000"
  };

  for (int i=0; i<5; i++) {
    itob(tests[i], s, 16);
    if (strcmp(s, hex_expected[i]))
      printf(
          "Expected %s for itob(%d, s, 16); got %s\n",
          hex_expected[i],
          tests[i], s
          );
  }
}

int itob(int n, char s[], int b)
{
  if (b > MAX_BASE)
    return -1;

  int sign;
  int i = 0;
  int overflow = 0;

  if (n == INT_MIN) {
    n += 1;
    overflow = 1;
  }

  if ((sign = n) < 0)
    n = -n;

  do {
    if (overflow) {
      overflow = handle_overflow(s, i, n, b);
      i++;
    } else {
      s[i++] = DIGITS[n % b];
    }
  } while ((n /= b) > 0);

  if (sign < 0)
    s[i++] = '-';

  s[i] = '\0';
  reverse(s);
  return 0;
}

int handle_overflow(char s[], int i, int n, int b) {
  if (n % b + 1 == b) {
    s[i] = '0';
    return 1;
  } else {
    s[i] = DIGITS[n % b] + 1;
    return 0;
  }
}

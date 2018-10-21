/* In a two's complement number system, our version of itoa does not handle
 * the largest negative number, that is, the value of n equal to
 * -(2^(wordsize-1)). Explain why not. Modify it to print that value
 *  correctly, regardless of the machine on which it runs. */

/* Why not: the largest negative number in two's complement is represented
 * by 1 followed by all 0s. The largest positive number is the inverse of this,
 * and therefore is one smaller than the absolute value of the largest negative.
 * In the first step, when we record the sign and flip it if the number is negative,
 * we would not get the same value since the positive complement is one less. */
#include <stdio.h>
#include <limits.h>
#include <string.h>

void itoa(int n, char s[]);
void itoa_prime(int n, char s[]);
void reverse(char s[]);

int main()
{
  char s[30];
  itoa(INT_MIN, s);
  printf("itoa(min, s):\n");
  itoa_prime(INT_MIN, s);
  printf("itoa_prime(INT_MIN, s): %s\n", s);
}

/* itoa: convert n to chars in s */
void itoa(int n, char s[])
{
  int i = 0;
  int sign;


  if ((sign = n) < 0)  /* record sign */
    n = -n;            /* make n positive */
  do {        /* generate digits in reverse order */
    s[i++] = n % 10 + '0';    /* get next digit */
  } while ((n /= 10) > 0);
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}
/* itoa_prime: convert n to chars in s,
 * account for INT_MIN */
void itoa_prime(int n, char s[])
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

  s[i] = '\0';
  reverse(s);
}

void reverse(char s[]) {
  int c, i, j;

  for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

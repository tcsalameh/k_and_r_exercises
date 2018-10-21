/* itoa: convert n to chars in s */
void itoa(int n, char s[])
{
  int i, sign;

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

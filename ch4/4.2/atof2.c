/* Extend atof to handle scientific notation of the form
 * 123.45e-6
 * where a floating-point number may be followed by e or E
 * or optionally a signed exponent. */
#include <stdio.h>
#include <ctype.h>
#include <math.h>

double atof(char s[]);
double calc_scientific(char s[], int i);

int main()
{
  char tests[][15] = {
    "123.456",
    "123.45e-6",
    "-123.45E6",
    "123.45*10^5"
  };

  double expected[] = {
    123.456,
    0.00012345,
    -123450000,
    12345000
  };

  for (int i = 0; i < 4; i++) {
    if (atof(tests[i]) != expected[i])
      printf("Expected %.8f for atof(%s), got %f.\n", expected[i], tests[i], atof(tests[i]));
  }
}

double atof(char s[])
{
  double val, power, base_exponent;
  int i, sign;

  for (i = 0; isspace(s[i]); i++) /* skip whitespace */
    ;

  sign = (s[i] == '-') ? -1 : 1;

  if (s[i] == '+' || s[i] == '-')
    i++;

  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');

  if (s[i] == '.')
    i++;

  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }

  base_exponent = calc_scientific(s, i);

  /* printf("%f * %f^%f\n", sign * val / power, base, exponent); */
  return (sign * val / power) * base_exponent;
}

double calc_scientific(char s[], int i)
{
  double base, exponent;
  int base_sign, exponent_sign;

  base = 10.0;
  base_sign = 1;
  if (s[i] == 'E' || s[i] == 'e') {
    i++;
    exponent_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
      i++;
    for (exponent = 0.0; isdigit(s[i]); i++)
      exponent = 10.0 * exponent + (s[i] - '0');
  }

  if (s[i] == '*') {
    i++;
    base_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
      i++;
    for (base = 0.0; isdigit(s[i]); i++)
      base = 10.0 * base + (s[i] - '0');
    if (s[i] == '^')
      i++;

    exponent_sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
      i++;
    for (exponent = 0.0; isdigit(s[i]); i++)
      exponent = 10.0 * exponent + (s[i] - '0');
  }

  base *= base_sign;
  exponent *= exponent_sign;
  return pow(base, exponent);
}

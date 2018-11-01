/* Write a recursive version of the function
 * reverse(s), which reverses the string in
 * place */
#include <stdio.h>
#include <string.h>

void reverse(char []);
void _reverse(char [], int, int);

int main()
{
  char tests[][30] = { "abba", "random string", "symb0l$ @nd numb3r$" };
  char expected[][30] = { "abba", "gnirts modnar", "$r3bmun dn@ $l0bmys" };

  for (int i=0; i<3; i++) {
    reverse(tests[i]);
    if (strcmp(tests[i], expected[i]))
      printf("expected %s for reverse, got %s\n", expected[i], tests[i]);
  }
}

void reverse(char s[])
{
  _reverse(s, 0, strlen(s) - 1);
}

void _reverse(char s[], int i, int j)
{
  int tmp;

  if (i >= j)
    return;

  tmp = s[i];
  s[i] = s[j];
  s[j] = tmp;
  _reverse(s, i+1, j-1);
}

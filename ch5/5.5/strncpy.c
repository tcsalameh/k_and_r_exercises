/* Write versions of the library functions _strncpy, strncat,
 * and strncmp, which operate on at most the first n characters
 * of their argument strings. For example, _strncpy(s,t,n) copies
 * at most n characters of t to s. */
#include <stdio.h>

void _strncpy(char *, char *, int n);

int main()
{
  char o[] = "this is a test string.";
  char s[] = "this is a test string";
  char t[] = "yet another test!";
  char *op = o;
  char *sp = s;
  char *tp = t;

  _strncpy(sp, tp, 5);
  printf("Got '%s' for _strncpy(%s, %s, 5)\n", s, o, t);

  _strncpy(s, t, 100);
  printf("Got '%s' for _strncpy(%s, %s, 100)\n", s, o, t);
}

void _strncpy(char *s, char *t, int n)
{
  for (int i = 0; i < n && (*s++ = *t++); i++)
    ;
}

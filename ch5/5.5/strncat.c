/* Write versions of the library functions _strncpy, strncat,
 * and strncmp, which operate on at most the first n characters
 * of their argument strings. For example, _strncpy(s,t,n) copies
 * at most n characters of t to s. */
#include <stdio.h>
#include <string.h>

void strn_cat(char *, char *, int n);

int main()
{
  char buf[100] = "hi! ";
  char *stringa = buf;
  char *stringb = "hello!";

  strn_cat(stringa, stringb, 3);
  printf("%s\n", stringa);

  strn_cat(stringa, stringb, 100);
  printf("%s\n", stringa);
}

void strn_cat(char *s, char *t, int n)
{
  for (;*s != '\0'; s++)
    ;
  for (int i = 0; i < n && (*s++ = *t++); i++)
    ;
  *s = '\0';
}

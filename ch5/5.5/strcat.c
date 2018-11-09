/* Write a pointer version of the function strcat from ch.2
 * strcat(s, t) copies the string t to the end of s */
#include <stdio.h>
#include <string.h>

void str_cat(char *, char *);

int main()
{
  char buf[100] = "hi! ";
  char *stringa = buf;
  char *stringb = "hello!";

  str_cat(stringa, stringb);
  printf("%s\n", stringa);
}

void str_cat(char *s, char *t)
{
  for (;*s != '\0'; s++)
    ;
  for (;(*s = *t) != '\0'; t++, s++)
    ;
  *s = '\0';
}

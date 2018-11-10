/* Rewrite appropriate programs from earlier chapters
 * and exercises with pointers instead of array indexing */
/* Write a function strindex(s, t) which returns the
 * position of the rightmost occurence of t in s, or
 * -1 if there is none */
#include <stdio.h>

#define MAX_LEN 1000    /* max line length we'll accept */

int strindex(char *, char *);

int main()
{
  char pattern[] = "ould";
  char *pp = pattern;
  char tests[][50] = {
    "",
    "a",
    "this one does not contain the string",
    "this one would contain the string twice, it should",
  };

  char *testsps[] = { tests[0], tests[1], tests[2], tests[3] };

  int expected[] = {-1, -1, -1, 46};
  int result;

  for (int i = 0; i < 4; i++) {
    result = strindex(*(testsps + i), pp);
    if (result != *(expected + i))
      printf("Expected %d for strindex('%s', '%s', got %d.\n", *(expected + i), *(testsps + i), pp, result);
  }
}

int strindex(char *s, char *t)
{
  char *start = s;
  char *i, *j;
  int result = -1;

  for (; *s != '\0'; s++) {
    for (i = t, j = s; *j != '\0' && *i == *j; i++, j++)
      ;
    if (i > t && *i == '\0')
      result = s - start;
  }

  return result;
}

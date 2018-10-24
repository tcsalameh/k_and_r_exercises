/* Write a function strindex(s, t) which returns the
 * position of the rightmost occurence of t in s, or
 * -1 if there is none */
#include <stdio.h>

#define MAX_LEN 1000    /* max line length we'll accept */

int strindex(char s[], char t[]);

int main()
{
  char pattern[] = "ould";
  char tests[][50] = {
    "",
    "a",
    "this one does not contain the string",
    "this one would contain the string twice, it should",
  };

  int expected[] = {-1, -1, -1, 46};
  int result;

  for (int i = 0; i < 4; i++) {
    result = strindex(tests[i], pattern);
    if (result != expected[i])
      printf("Expected %d for strindex('%s', '%s'), got %d.\n", expected[i], tests[i], pattern, result);
  }
}

int strindex(char s[], char t[])
{
  int i, j, k;
  int result = -1;

  for (i = 0; s[i] != '\0'; i++) {
    for (j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      result = i;
  }
  return result;
}

/* Write a function strend(s,t) which returns 1 if the
 * string t occurs at the end of the string s, and 0 otherwise */
#include <stdio.h>
#include <string.h>

int strend(char *, char *);

int main()
{
  char *s = "hi! hello!";
  char *t = "hello!";
  char *u = "he";

  if (!strend(s, t))
    printf("Expected 1 for strend(%s, %s), got %d\n", s, t, strend(s, t));

  if (strend(s, u))
    printf("Expected 0 for strend(%s, %s), got %d\n", s, u, strend(s, u));
}

int strend(char *s, char *t)
{
  int s_len = strlen(s);
  int t_len = strlen(t);
  if (s_len < t_len)
    return 0;

  char *start = (s + s_len) - (t_len);

  for (char *start = s + s_len - t_len; *start != '\0'; start++, t++)
    if (*start != *t)
      return 0;

  return 1;
}

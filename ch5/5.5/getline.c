/* Rewrite appropriate programs from earlier chapters
 * and exercises with pointers instead of array indexing */
#include <stdio.h>

#define MAXLINE 1000    /* Max line we can get */

int getLine(char *, int limit);

int main()
{
  char s[MAXLINE];
  char *ps = s;
  int len;

  while ((len = getLine(ps, MAXLINE)) != 0) {
    printf("%s %d\n", s, len);
  }
}


int getLine(char *line, int limit)
{
  int c;
  char *counter = line;

  for (; (c = getchar()) != EOF && c != '\n'; counter++)
    *counter = c;

  if (c == '\n') {
    *counter++ = c;
  }
  *counter = '\0';
  return counter - line - 1;
}

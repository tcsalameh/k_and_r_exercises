#include <stdio.h>
#define MAXLINE 1000     /* max line length we can print */

int getLine(char line[], int limit);
void copy(char to[], char from[]);

int getLine(char line[], int limit)
{
  int c, i;

  for (i=0; (i < limit-1) && (c=getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;

  if (c == '\n') {
    line[i] = c;
    ++i;
  }
  line[i] = '\0';
  return i;
}

void copy(char to[], char from[])
{
  int i;
  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}

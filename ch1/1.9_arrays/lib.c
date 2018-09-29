#include <stdio.h>
#define MAXLINE 1000     /* max line length we can print */

int getLine(char line[], int limit);
void reverse(char line[]);
void copy(char to[], char from[]);
int length(char line[]);

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

int length(char line[])
{
  int l;
  for (l=0; line[l] != '\0'; l++)
    ;
  return l;
}

void reverse(char line[])
{
  int l, j;

  l = length(line);

  char line_copy[l];

  for (int i=0; i<l; i++)
    line_copy[i] = line[i];

  j = 0;
  // start at l-2 so we don't reverse
  // the trailing newline
  for (int i=l-2; i >= 0; --i) {
    line[j] = line_copy[i];
    ++j;
  }
}

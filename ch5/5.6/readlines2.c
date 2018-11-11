/* Rewrite readlines to store lines in an array supplied
 * by main, rather than calling alloc to maintain storage.
 * How much faster is the program? */
#include <string.h>
#include <stdio.h>

#define MAXLINES  5000       /* max # lines to be sorted */
#define MAXLEN    1000       /* max length of any input line */

int getLine(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], char lines[], int maxlines)
{
  int len, nlines;
  char *p, *i, line[MAXLEN];

  nlines = 0;
  i = lines;
  while ((len = getLine(line, MAXLEN)) > 0)
      if (nlines >= maxlines)
        return -1;
      else {
        line[len-1] = '\0'; /* delete newline */
        strcpy(i, line);
        p = i;
        i += len;
        lineptr[nlines++] = p;
      }
  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  int i;

  for (i = 0; i < nlines; i++)
    printf("%s\n", lineptr[i]);
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
  return counter - line;
}

#include <string.h>
#include <stdio.h>

#define ALLOCSIZE 10000    /* size of available space */
#define MAXLEN 1000    /* max length of any input line */

int getLine(char *, int);
char *alloc(int);
void afree(char *);
static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = getLine(line, MAXLEN)) > 0)
      if (nlines >= maxlines || (p = alloc(len)) == NULL)
        return -1;
      else {
        line[len-1] = '\0'; /* delete newline */
        strcpy(p, line);
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

char *alloc(int n)  /* return pointer to n chars */
{
  if (allocbuf + ALLOCSIZE - allocp >= n) {
    allocp += n;
    return allocp - n;
  } else
    return 0;
}

void afree(char *p)  /* free storage pointed to by p */
{
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
    allocp = p;
}

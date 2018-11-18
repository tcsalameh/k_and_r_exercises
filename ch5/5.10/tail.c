/* Write the program tail, which prints the last n lines of its input.
 * By default, n is 10, let us say, but can be change by an optional
 * argument, such that:
 *    tail -n
 * prints the last n lines. The program should behave rationally no matter
 * how unreasonable the input or the value of n. Write the program so it makes
 * the best use of available storage; lines should be stored as in the sorting
 * program of section 5.6, not in a two-dimensional array of fixed size. */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>  /* for atof() */

#define DEFAULT_TAIL_SIZE 10
#define MAXLINES          1000
#define ALLOCSIZE         10000    /* size of available space */
#define MAXLEN            1000     /* max length of any input line */

char *lineptr[MAXLINES];  /* pointers to text lines */
char usage[500];
static char allocbuf[ALLOCSIZE];    /* storage for alloc */
static char *allocp = allocbuf;     /* next free position */

int parseargs(int argc, char *argv[]);
int is_neg_int(char *);
int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int getLine(char *, int);
char *alloc(int);
void afree(char *);

int main(int argc, char *argv[])
{
  int nlines;    /* number of input lines read */
  int ntail;     /* number of lines to tail */

  sprintf(usage, "Usage:\n  tail [-n]           Print last n lines of the input, n defaults to %d.\n\n", DEFAULT_TAIL_SIZE);

  if ((ntail = parseargs(argc, argv)) < 0) {
      printf("%s", usage);
      return 1;
  }

  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    ntail = (nlines > ntail) ? ntail : nlines;
    char **start = lineptr + nlines - ntail;
    writelines(start, ntail);
  }
}

int is_neg_int(char *input)
{
  if (*input == '\0')
    return 0;

  if (*input == '-')
    input++;
  else
    return 0;

  for (; *input != '\0'; input++)
    if (!isdigit(*input))
      return 0;

  return 1;
}

int parseargs(int argc, char *argv[])
{
  if (argc > 2)
    return -1;

  if (argc == 1)
    return DEFAULT_TAIL_SIZE;

  if (is_neg_int(*(++argv))) {
    return atof(*argv) * -1;
  } else
    return -1;
}

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

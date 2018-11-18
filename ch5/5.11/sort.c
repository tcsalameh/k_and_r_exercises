/* 5-14: Modify the sort program to handle a -r flag, which
 * indicates sorting in reverse (decreasing) order. Be sure
 * that -r works with -n. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000     /* max #lines that we can sort */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void q_sort(void *lineptr[], int left, int right, int reverse,
           int (*comp) (void *, void *));
int numcmp(char *, char *);
int parseargs(int argc, char *argv[], int parsedargs[]);

/* sort input lines */
int main (int argc, char *argv[])
{
  int nlines;         /* number of input lines read */
  int numeric;        /* whether to sort by numeric value */
  int reverse;        /* sort in reverse order */

  int args[] = {
    0, // numeric
    1  // reverse
  };
  if (!parseargs(argc, argv, args)) {
    printf("Error parsing arguments\n");
    return 1;
  }

  numeric = args[0];
  reverse = args[1];
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    q_sort((void **) lineptr, 0, nlines -1, reverse,
        (int (*)(void*,void*)) (numeric ? numcmp : strcmp));
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

int parseargs(int argc, char *argv[], int parsedargs[])
{
  while (--argc > 0 && ++argv) {
    if (strcmp(*argv, "-n") == 0)
        parsedargs[0] = 1;
    else if (strcmp(*argv, "-r") == 0)
        parsedargs[1] = -1;
    else
      return 0;
  }

  return 1;
}


/* qsort: sort v[left]...v[right] into increasing order */
void q_sort(void *v[], int left, int right, int reverse,
           int (*comp)(void *, void *))
{
  int i, last;
  void swap(void *v[], int, int);

  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left+1; i<= right; i++)
    if ((*comp)(v[i], v[left]) * reverse < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  q_sort(v, left, last-1, reverse, comp);
  q_sort(v, last+1, right, reverse, comp);
}

/* numcpm: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

void swap(void *v[], int i, int j)
{
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

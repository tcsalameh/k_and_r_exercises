/* Rewrite readlines to store lines in an array supplied
 * by main, rather than calling alloc to maintain storage.
 * How much faster is the program? */
#include <stdio.h>
#include <string.h>

#define MAXLINES        5000       /* max # lines to be sorted */
#define MAXLEN          1000       /* max # lines to be sorted */

char *lineptr[MAXLINES];  /* pointers to text lines */
char lines[MAXLINES][MAXLEN];

int readlines(char *lineptr[], char lines[MAXLINES][MAXLEN], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
  int nlines;    /* number of input lines read */

  if ((nlines = readlines(lineptr, lines, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right)
    return;
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[left]) > 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qsort(v, left, last-1);
  qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

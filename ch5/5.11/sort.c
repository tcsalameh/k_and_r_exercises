/* 5-14: Modify the sort program to handle a -r flag, which
 * indicates sorting in reverse (decreasing) order. Be sure
 * that -r works with -n. */
/* 5-15: Add the option -f to fold upper and lower case together,
 * so that case distinctions are not made during sorting. For
 * example, a and A compare equal */
/* 5-16: Add the -d (directory order) option, which makes
 * comparisons only on letters, numbers, and blanks. Make sure it
 * works in conjunction with -f. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000     /* max #lines that we can sort */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void q_sort(void *lineptr[], int left, int right, int reverse,
           int fold, int directory, int (*comp) (void *, void *));
int numcmp(char *, char *);
int parseargs(int argc, char *argv[], int parsedargs[]);
void lower(char *);
void dirformat(char *, char *);

/* sort input lines */
int main (int argc, char *argv[])
{
  int nlines;         /* number of input lines read */
  int numeric;        /* whether to sort by numeric value */
  int reverse;        /* sort in reverse order */
  int fold;           /* fold upper and lower case chars together */
  int dir;           /* directory order, ignore non-alphanumeric chars */

  int args[] = {
    0, // numeric
    1, // reverse
    0, // fold
    0  // dir
  };
  if (!parseargs(argc, argv, args)) {
    printf("Error parsing arguments\n");
    return 1;
  }

  numeric = args[0];
  reverse = args[1];
  fold = args[2];
  dir = args[3];
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    q_sort((void **) lineptr, 0, nlines - 1, reverse, fold, dir,
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
    else if (strcmp(*argv, "-f") == 0)
        parsedargs[2] = 1;
    else if (strcmp(*argv, "-d") == 0)
        parsedargs[3] = 1;
    else
      return 0;
  }

  return 1;
}


/* qsort: sort v[left]...v[right] into increasing order */
void q_sort(void *v[], int left, int right, int reverse, int fold, int directory,
           int (*comp)(void *, void *))
{
  int i, last;
  void swap(void *v[], int, int);

  if (left >= right)
    return;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left+1; i<= right; i++) {
    if (fold || directory) {
      char rcopy[strlen(v[i])], lcopy[strlen(v[left])];
      directory ? dirformat(rcopy, v[i]) : strcpy(rcopy, v[i]);
      directory ? dirformat(lcopy, v[left]) : strcpy(lcopy, v[left]);
      if (fold) {
        lower(rcopy);
        lower(lcopy);
      }
      if ((*comp)(rcopy, lcopy) * reverse < 0)
        swap(v, ++last, i);
    } else {
      if ((*comp)(v[i], v[left]) * reverse < 0)
        swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  q_sort(v, left, last-1, reverse, fold, directory, comp);
  q_sort(v, last+1, right, reverse, fold, directory, comp);
}

/* replaces str with lowercase version */
void lower(char *str)
{
  for (;*str != '\0'; str++)
    *str = (*str <= 'Z' && *str >= 'A') ? *str + 32: *str;
}

/* removes all chars that are not letters, numbers, or blanks */
void dirformat(char *cpy, char *str)
{
  char *orig = str;
  char *ocopy = cpy;
  for (; *str != '\0'; str++) {
    if ((*str >= 'A' && *str <= 'Z') ||
        (*str >= 'a' && *str <= 'z') ||
        (*str >= '0' && *str <= '9') ||
        *str == ' ' || *str == '\t') {
      *cpy = *str;
      cpy++;
    }
  }
  *cpy = '\0';
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

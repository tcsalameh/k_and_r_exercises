/* 5-14: Modify the sort program to handle a -r flag, which
 * indicates sorting in reverse (decreasing) order. Be sure
 * that -r works with -n. */
/* 5-15: Add the option -f to fold upper and lower case together,
 * so that case distinctions are not made during sorting. For
 * example, a and A compare equal */
/* 5-16: Add the -d (directory order) option, which makes
 * comparisons only on letters, numbers, and blanks. Make sure it
 * works in conjunction with -f. */
/* 5-17: Add a field handling capability, so sorting may be done
 * on fields within lines, each field sorted according to an
 * independent set of options. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000     /* max #lines that we can sort */

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

int q_sort(void *lineptr[], int left, int right,
            int reverse, int fold, int directory,
            int fieldnum, char fieldsep,
            int (*comp) (void *, void *));
int numcmp(char *, char *);
int parseargs(int argc, char *argv[], char parsedargs[]);
void lower(char *);
void dirformat(char *, char *);
int cut(char *, int, char);

/* sort input lines */
int main (int argc, char *argv[])
{
  int nlines;         /* number of input lines read */
  int numeric;        /* whether to sort by numeric value */
  int reverse;        /* sort in reverse order */
  int fold;           /* fold upper and lower case chars together */
  int dir;            /* directory order, ignore non-alphanumeric chars */
  int fieldnum;       /* field number to sort on */
  char sep;           /* seperator for fields */

  char args[] = {
    0,   // numeric
    1,   // reverse
    0,   // fold
    0,   // dir
    -1,  // fieldnum
    ' ', // seperator
  };
  if (!parseargs(argc, argv, args)) {
    printf("Error parsing arguments\n");
    return 1;
  }

  numeric = args[0];
  reverse = args[1];
  fold = args[2];
  dir = args[3];
  fieldnum = args[4];
  sep = args[5];

  int status = 0;
  if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    status = q_sort((void **) lineptr, 0, nlines - 1,
           reverse, fold, dir, fieldnum, sep,
           (int (*)(void*,void*)) (numeric ? numcmp : strcmp));
    if (status != 1)
      writelines(lineptr, nlines);
    return status;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

int parseargs(int argc, char *argv[], char parsedargs[])
{
  while (--argc > 0 && ++argv) {
    if (strcmp(*argv, "-n") == 0)
      // numeric sort
      parsedargs[0] = 1;
    else if (strcmp(*argv, "-r") == 0)
      // reverse order
      parsedargs[1] = -1;
    else if (strcmp(*argv, "-f") == 0)
      // treat upper/lower case the same
      parsedargs[2] = 1;
    else if (strcmp(*argv, "-d") == 0)
      // directory order
      parsedargs[3] = 1;
    else if (strcmp(*argv, "-F") == 0) {
      // field number to sort on
      parsedargs[4] = atof(*(++argv));
      argc--;
    }
    else if (strcmp(*argv, "-s") == 0) {
      // field separator
      parsedargs[5] = *(++argv)[0];
      argc--;
    }
    else
      return 0;
  }

  return 1;
}


/* qsort: sort v[left]...v[right] into increasing order */
int q_sort(void *v[], int left, int right,
            int reverse, int fold, int directory,
            int fieldnum, char fieldsep,
            int (*comp)(void *, void *))
{
  int i, last;
  void swap(void *v[], int, int);

  if (left >= right)
    return 0;
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left+1; i<= right; i++) {
    if (fold || directory || fieldnum >= 0) {
      char l[strlen(v[i])], r[strlen(v[left])];
      char *rcopy = l;
      char *lcopy = r;
      directory ? dirformat(rcopy, v[i]) : strcpy(rcopy, v[i]);
      directory ? dirformat(lcopy, v[left]) : strcpy(lcopy, v[left]);
      if (fold) {
        lower(rcopy);
        lower(lcopy);
      }
      if (fieldnum >= 0) {
        int rstart = cut(rcopy, fieldnum, fieldsep);
        int lstart = cut(lcopy, fieldnum, fieldsep);
        if (rstart >= 0)
          rcopy += rstart;
        else {
          printf("ERROR: String '%s' has fewer than %d fields separated by '%c'.\n", v[i], fieldnum + 1, fieldsep);
          return 1;
        }
        if (lstart >= 0)
          lcopy += lstart;
        else {
          printf("ERROR: String '%s' has fewer than %d fields separated by '%c'.\n", v[left], fieldnum + 1, fieldsep);
          return 1;
        }
      }
      if ((*comp)(rcopy, lcopy) * reverse < 0)
        swap(v, ++last, i);
    } else {
      if ((*comp)(v[i], v[left]) * reverse < 0)
        swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  return q_sort(v, left, last-1, reverse, fold, directory, fieldnum, fieldsep, comp);
  return q_sort(v, last+1, right, reverse, fold, directory, fieldnum, fieldsep, comp);
}

/* return how far forward the field begins
 * relative to pointer
 * and set the end of the field to '\0' */
int cut(char *str, int fieldnum, char sep)
{
  int fieldcount = 0;
  int i = 0;

  while (str[i] != '\0') {
    if (fieldcount == fieldnum) {
      int j = i;
      for (; str[j] != '\0' && str[j] != sep; j++)
        ;
      str[j] = '\0';
      return i;
    }
    if (str[i] == sep) {
      fieldcount++;
      while (str[++i] == sep)
        ;
    } else
      i++;
  }
  return -1;
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

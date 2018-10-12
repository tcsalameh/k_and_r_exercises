#include <stdio.h>

#define LINELIMIT 80    /* where to wrap when breaking lines */
#define MAXLINE 1000    /* largest line we'll operate on */

int getLine(char line[], int limit);
void printLine(char line[], int start, int end);
int scanLineBackwards(char line[], int start, int end);

/* Fold longer lines into two or more shorter lines
 * after the last non-blank character that occurs before the n-th column of input.
 */
int main()
{
  char line[MAXLINE];
  int breakpoint, first, last, len;

  while ((len = getLine(line, MAXLINE)) != 0) {
    if (len <= LINELIMIT) {
      printf("%s", line);
    } else {
      first = 0;
      last = LINELIMIT;
      while (last < len) {
        breakpoint = scanLineBackwards(line, last, first);
        if (breakpoint == -1) {
          printLine(line, first, last);
          first += LINELIMIT;
          last += LINELIMIT;
        } else {
          printLine(line, first, breakpoint);
          first = breakpoint;
          last = breakpoint + LINELIMIT;
        }
      }
      printLine(line, first, len);
    }
  }
}

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

void printLine(char line[], int start, int end) {
  for (start; line[start] == ' ' || line[start] == '\t'; ++start)
    ;
  for (start; start<end; ++start)
    printf("%c", line[start]);

  if (line[start-1] != '\n')
    printf("%c", '\n');
}

int scanLineBackwards(char line[], int start, int end) {
  while (start > end) {
    if (line[start] == ' ' || line[start] == '\t'
        && line[start-1] != ' ' && line[start-1] != '\t') {
      return start;
    }
    --start;
  }

  return -1;
}

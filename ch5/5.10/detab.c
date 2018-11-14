/* Modify the programs entab and detab to accept a list of
 * tab stops as arguments. Use the default tab settings if
 * there are no arguments. */
#include <stdio.h>
#include <stdlib.h>  /* for atof() */

#define DEFAULT_TAB_SIZE 2    /* Spaces per tab */
#define MAXLINE 1000

int getLine(char *line, int max);

/* Replaces all tabs in the input with TAB_SIZE spaces */
int main(int argc, char *argv[])
{
  int len;
  char s[MAXLINE];
  char tabstops[MAXLINE];
  char *sp = s;

  if (argc > 1) {
    int ts_idx;
    for (ts_idx = 0; --argc > 0; ts_idx++)
      tabstops[ts_idx] = atof(*(++argv));

    for (; ts_idx < MAXLINE; ts_idx++) {
      tabstops[ts_idx] = tabstops[ts_idx-1] + DEFAULT_TAB_SIZE;
    }
  } else {
    for (int i = 0; i < MAXLINE; i++)
      tabstops[i] = DEFAULT_TAB_SIZE * i;
  }

  while ((len = getLine(sp, MAXLINE)) != 0) {
    // if we find a tab character
    // print spaces and add until we get to the next tabstop
    char *tsp = tabstops;
    for (int i = 0, colno = 0; sp[i] != '\n'; i++) {
      if (sp[i] == '\t') {
        for (; *tsp <= colno; tsp++)
         ;
        for (; colno<*tsp; colno++) {
          printf(" ");
        }
      } else {
        printf("%c", sp[i]);
        colno++;
      }
    }
    printf("\n");
  }
}

/* getLine: get line into s, return length */
int getLine(char *sp, int lim)
{
  int c;

  char *counter = sp;
  while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
    *counter++ = c;
  if (c == '\n')
    *counter++ = c;
  *counter = '\0';
  return counter - sp;
}

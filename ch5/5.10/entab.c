/* Modify the programs entab and detab to accept a list of
 * tab stops as arguments. Use the default tab settings if
 * there are no arguments. */
#include <stdio.h>
#include <stdlib.h>  /* for atof() */

#define DEFAULT_TAB_SIZE 2    /* Spaces per tab */
#define MAXLINE 1000

int getLine(char *line, int max);

// strategy
// consume each line until the next tabstop
// then, go backwards from the tabstop while there are spaces
// once you hit no spaces, enter a tab character next
// then skip to the tabstop, and read again until the next tabstop
/* Replaces TAB_SIZE spaces in the input with tabs */
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

  int i, tabstart;
  while ((len = getLine(sp, MAXLINE)) != 0) {
    char *tsp = tabstops;
    i = 0;
    while (*tsp <= len) {
      tabstart = *tsp - 1;
      if (tabstart > 0) {
        while (sp[tabstart] == ' ' && tabstart > i)
          tabstart--;
      }
      for (; i <= tabstart; i++)
        printf("%c", sp[i]);
      if (*tsp - i > 0)
        printf("\t");
      i = *tsp;
      tsp++;
    }
    for (; i < len; i++)
      printf("%c", sp[i]);
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

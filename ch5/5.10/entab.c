/* Modify the programs entab and detab to accept a list of
 * tab stops as arguments. Use the default tab settings if
 * there are no arguments. */
/* Extend entab and detab to accept the shorthand
 *    entab -m +n
 * to mean tab stops every n columns, starting at column m.
 * Choose convenient (for the user) default behavior */
#include <stdio.h>
#include <stdlib.h>  /* for atof() */

#define DEFAULT_TAB_SIZE 2    /* Spaces per tab */
#define MAXLINE          1000

char usage[500];

int getLine(char *line, int max);
int parseargs(int argc, char *argv[], char *tabstops);

/* Replaces TAB_SIZE spaces in the input with tabs */
int main(int argc, char *argv[])
{
  int len;
  char s[MAXLINE];
  char tabstops[MAXLINE];
  char *sp = s;
  char *tsp = tabstops;

  sprintf(usage, "Usage:\n"\
  "  entab               Defaults to a tabstop every %d columns.\n"\
  "  entab -m +n         Set tabstops every n columns starting at column m.\n"\
  "  entab t1 t2 t3...   Set tabstops at column t1, t2, t3, etc.\n"\
  "                      Remaining tabstops will be every %d columns.\n\n",
  DEFAULT_TAB_SIZE,
  DEFAULT_TAB_SIZE);

  if (parseargs(argc, argv, tsp)) {
      printf("%s", usage);
      return 1;
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

int parseargs(int argc, char *argv[], char *tabstops)
{
  int m;
  int n;
  char *start = tabstops;

  if (argc < 2) {
    for (int i = 0; i < MAXLINE; i++)
      tabstops[i] = DEFAULT_TAB_SIZE * i;
    return 0;
  } else {
    ++argv;
    for (; --argc > 0; argv++) {
      if (*argv[0] == '-' || *argv[0] == '+') {
        if (*argv[0] == '-') {
          m = atof(*argv) * -1;
          while (*argv[0] != '+' && --argc > 0)
            argv++;
          if (argc <= 1 && *argv[0] != '+')
            return 1;
          n = atof(*argv);
        } else {
          n = atof(*argv);
          while (*argv[0] != '-' && --argc > 0)
            argv++;
          if (argc <= 1 && *argv[0] != '-')
            return 1;
          m = atof(*argv) * -1;
        }

        tabstops[0] = m;
        for (int i = 1; i < MAXLINE; i++)
          tabstops[i] = tabstops[i-1] + n;
        return 0;
      }
      else {
        *tabstops++ = atof(*argv);
      }
    }
  }
  for (; tabstops - start < MAXLINE; tabstops++) {
    *tabstops = *(tabstops-1) + DEFAULT_TAB_SIZE;
  }
  return 0;
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

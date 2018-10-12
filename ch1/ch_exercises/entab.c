#include <stdio.h>
#include <stdbool.h>

#define TAB_SIZE 2     /* Spaces per tab */
#define MAXLINE  1000  /* max line length */

int getLine(char line[], int limit);

/* Replace multiple spaces in the input with tabs,
 * based on TAB_SIZE */
int main()
{
  char line[MAXLINE]; /* current line */
  char buffer[TAB_SIZE];
  int len;
  bool all_spaces;

  while ((len = getLine(line, MAXLINE)) > 0) {
    int i = 0;
    while (i < len) {
      all_spaces = true;
      for (int j=0; j<TAB_SIZE; ++j) {
        if (line[i] != ' ')
          all_spaces = false;
        buffer[j] = line[i];
        ++i;
      }
      if (all_spaces) {
        printf("%c", '\t');
      } else {
        for (int j=0; j<TAB_SIZE && buffer[j] != '\0'; ++j)
          printf("%c", buffer[j]);
      }
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

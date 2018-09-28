#include <stdio.h>
#include "lib.c"

int main()
{
  int len;
  char line[MAXLINE];            /* current line */

  while ((len = getLine(line, MAXLINE)) != 0) {
    int j = len - 1;

    while (j > 0 && (line[j] == '\n' || line[j] == ' ' || line[j] == '\t'))
      --j;

    if (j != 0) {
      for (int k = 0; k <= j; ++k)
        printf("%c", line[k]);
      printf("\n");
    }
  }
}

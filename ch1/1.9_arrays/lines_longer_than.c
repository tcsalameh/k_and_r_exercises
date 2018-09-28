#include <stdio.h>
#include "lib.c"
#define MAXLINE 1000     /* max line length we can print */
#define MINLINE 80       /* print all lines longer than this */

main()
{
  int len;
  char line[MAXLINE];

  while ((len = getLine(line, MAXLINE)) != 0)
    if (len > MINLINE)
      printf("%s", line);
}

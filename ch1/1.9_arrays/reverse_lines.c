#include <stdio.h>
#include "lib.c"

main()
{
  int len;
  char line[MAXLINE];

  while ((len = getLine(line, MAXLINE)) != 0) {
    reverse(line);
    printf("%s", line);
  }
}

#include <stdio.h>

/* counts blanks, tabs, newlines in input text */
main()
{
  int c, line_count;

  line_count = 0;
  while ((c = getchar()) != EOF) {
    if (c == '\n' || c == '\t' || c == ' ')
      ++line_count;
  }

  printf("Number of lines, spaces, and tabs: %d", line_count);
}

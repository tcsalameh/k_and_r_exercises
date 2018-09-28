#include <stdio.h>

/* replace one or more blanks with single blank in output */
main()
{
  int c, prev;

  prev = EOF;
  while ((c = getchar()) != EOF) {
    if (!(prev == ' ' && c == ' ')) {
      printf("%c", c);
    }
    prev = c;
  }
}

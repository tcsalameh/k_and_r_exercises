#include <stdio.h>

#define IN  0    /* in a word */
#define OUT 1    /* outside of a word */

/* prints input with one word on each line */
main()
{
  int c, state;
  c = 0;
  state = OUT;

  while ((c = getchar()) != EOF) {
    if (c == ' ' || c == '\t' || c == '\n') {
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      printf("\n");
    }
    if (c != ' ' || c != '\t' || c != '\n')
      printf("%c", c);
  }
}

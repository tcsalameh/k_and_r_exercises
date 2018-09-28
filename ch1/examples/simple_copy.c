#include <stdio.h>

/* copy input to output */
main()
{

  /* int is used instead of char because
   * int has a large enough range to return any possible value
   * received by getchar(). char does not have a large
   * enough range to hold EOF values */
  int c;

  while ((c = getchar()) != EOF) {
    putchar(c);
  }
}

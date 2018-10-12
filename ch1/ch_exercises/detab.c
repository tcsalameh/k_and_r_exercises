#include <stdio.h>

#define TAB_SIZE 2    /* Spaces per tab */

/* Replaces all tabs in the input with TAB_SIZE spaces */
int main()
{
  int c;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      for (int i=0; i<TAB_SIZE; ++i)
        printf(" ");
    } else {
      printf("%c", c);
    }
  }
}

#include <stdio.h>

/* replace each tab in input with \t, each backspace with \b, and each backslash with \\ */
main()
{
  int c;

  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      printf("\\t");
    } else if (c == '\b') {
      printf("\\b");
    } else if (c == '\\') {
      printf("\\");
    } else {
      printf("%c", c);
    }
  }
}

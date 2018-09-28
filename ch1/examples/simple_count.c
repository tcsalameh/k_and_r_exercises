#include <stdio.h>

/* Count characters in input */
main()
{
  long char_count = 0;

  while (getchar() != EOF)
    ++char_count;
  printf("Total characters in input: %d", char_count);
}

#include <stdio.h>

/* Count characters in input, take 2 */
main()
{
  double char_count;

  for (char_count = 0; getchar() != EOF; ++char_count)
    ;

  printf("Total characters in input: %.0f", char_count);
}

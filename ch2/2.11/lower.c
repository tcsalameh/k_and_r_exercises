/* Rewrite the function lower, which converts upper case letters
 * to lower case, with a conditional expression instead of if-else.
 */
#include <stdio.h>
#include <ctype.h>

char lower(char c);

int main()
{
  char test[9] = "AZXxa\%.Gf";

  for (int i=0; test[i]!='\0'; i++) {
    if (lower(test[i]) != tolower(test[i]))
      printf("Test %d failed: expected %c for lower(%c), got %c\n", i, tolower(test[i]), test[i], lower(test[i]));
  }
}

char lower(char c)
{
  return ('A' <= c && c <= 'Z') ? c + 32 : c;
}

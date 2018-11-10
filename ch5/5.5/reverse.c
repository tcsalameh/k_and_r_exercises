/* Rewrite appropriate programs from earlier chapters
 * and exercises with pointers instead of array indexing */
#include <stdio.h>
#include <string.h>

void reverse(char *);

int main()
{
  char test[] = "abc123";
  char *tp = test;

  reverse(tp);
  printf("Expected 321cba, got %s\n", tp);
}

void reverse(char *s)
{
  int tmp;
  char *j = s + strlen(s) - 1;

  for (; s < j; s++, j--) {
    tmp = *s;
    *s = *j;
    *j = tmp;
  }
}

/* Write versions of the library functions _strncpy, strncat,
 * and strn_cmp, which operate on at most the first n characters
 * of their argument strings. For example, _strncpy(s,t,n) copies
 * at most n characters of t to s. */
#include <stdio.h>

int strn_cmp(char *s, char *t, int n);

int main()
{
  char s[] = "test string 1";
  char t[] = "test string 2";
  char o[] = "test string 1";

  char *sp = s;
  char *tp = t;
  char *op = o;

  /* expect 0 for s vs. o with all chars */
  if (strn_cmp(sp, op, 100) != 0)
    printf("Expected 0 for strn_cmp(%s, %s, 100), got %d\n", sp, op, strn_cmp(sp, op, 100));
  /* expect 0 for s vs. t with 12 chars*/
  if (strn_cmp(sp, tp, 12) != 0)
    printf("Expected 0 for strn_cmp(%s, %s, 12), got %d\n", sp, tp, strn_cmp(sp, tp, 12));
  /* expect 1 for t vs s with all chars */
  if (strn_cmp(tp, sp, 100) <= 0)
    printf("Expected >0 for strn_cmp(%s, %s, 100), got %d\n", tp, sp, strn_cmp(tp, sp, 100));
  /* expect -1 for s vs t with all chars */
  if (strn_cmp(sp, tp, 100) >= 0)
    printf("Expected <0 for strn_cmp(%s, %s, 100), got %d\n", sp, tp, strn_cmp(sp, tp, 100));
}

int strn_cmp(char *s, char *t, int n)
{
  for (int i = 1; i < n && (*s == *t); s++, t++, i++)
    if (*s == '\0')
      return 0;
  return *s - *t;
}

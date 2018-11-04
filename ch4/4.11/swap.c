/* Define a macro swap(t, x, y) that interchanges
 * two arguments of type t. (Block structure will help).
 * */
#include <stdio.h>

#define swap(t,x,y) { t tmp = x; x = y; y = tmp; }

int main()
{
  int x = 5;
  int y = 6;
  printf("x: %d, y: %d\n", x, y);

  swap(int, x, y);

  printf("x: %d, y: %d\n", x, y);
}

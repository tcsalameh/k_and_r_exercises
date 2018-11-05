#include <stdio.h>

int main()
{
  int x = 1, y = 2, z[10];
  int *ip;

  printf("%d, %d, %d\n", x, y, ip);
  // 1, 2, mem loc of int

  ip = &x;
  printf("%d, %d, %d\n", x, y, ip);
  // 1, 2, mem loc of x

  y = *ip;
  printf("%d, %d, %d\n", x, y, ip);
  // 1, 1, mem loc of x

  *ip = 0;
  printf("%d, %d, %d\n", x, y, ip);
  // 0, 1, mem loc of x
}

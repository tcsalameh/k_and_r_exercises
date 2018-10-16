/* Write a function rightrot(x, n) that returns
 * the value of the integer x rotated to the right
 * by n bit positions */
#include <stdio.h>
#include <math.h>
#include "bits.h"

unsigned rightrot(unsigned, int);
unsigned rotateright(unsigned);
int find_power(unsigned);

int main()
{
  unsigned tests[10] = {0x0, 0x1, 0x9, 0x2a, 0x32};

  unsigned expected[][2] = {
    // 0 rotated right by any pos is still 0
    {0x0, 0x0},
    // 1 rotated right by any pos is still 1
    {0x1, 0x1},
    // 1001 rotated right by 2 is 110, by 5 is 11
    {0x6, 0x3},
    // 101010 rotated right by 2 = 11010, by 5 is 1110
    {0x1a, 0x7},
    // 110010 rotated right by 2 = 11100, by 5 is 111
    {0x1c, 0x7}
  };


  for (int i=0; i<5; i++) {
    if (rightrot(tests[i], 0) != tests[i])
      printf("Test %d failed: expected 0x%x for rightrot(0x%x, 0), got 0x%x\n", i, tests[i], tests[i], rightrot(tests[i], 0));
    if (rightrot(tests[i], 2) != expected[i][0])
      printf("Test %d failed: expected 0x%x for rightrot(0x%x, 2), got 0x%x\n", i, expected[i][0], tests[i], rightrot(tests[i], 2));
    if (rightrot(tests[i], 5) != expected[i][1])
      printf("Test %d failed: expected 0x%x for rightrot(0x%x, 5), got 0x%x\n", i, expected[i][1], tests[i], rightrot(tests[i], 5));
  }
}

unsigned rightrot(unsigned x, int n) {
  for (; n>0; n--)
    x = rotateright(x);
  return x;
}

unsigned rotateright(unsigned x) {
  unsigned mask = getbits(x, 0, 1) << (find_power(x));
  return mask | (x >> 1);
}

int find_power(unsigned x) {
  int i;
  for (i=0; pow(2, i) < x; i++)
    ;
  if (i > 0)
    return i-1;
  else
    return i;
}

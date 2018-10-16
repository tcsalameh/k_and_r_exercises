/* Write a function invert(x,p,n) that returns x
 * with the n bits that begin at position p inverted,
 * leaving the others unchanged */
#include <stdio.h>
#include "bits.h"

unsigned invert(unsigned, int, int);

int main()
{

  unsigned tests[10] = {0x0, 0x1, 0x6, 0x3f, 0x25};

  unsigned expected[][2] = {
    {0x1, 0xe},
    {0x0, 0xf},
    {0x7, 0x8},
    {0x3e, 0x31},
    {0x24, 0x2b}
  };

  for (int i=0; i<5; i++) {
    if (invert(tests[i], 0, 0) != tests[i])
      printf("Test %d failed: expected 0x%x, got 0x%x\n", i, tests[i], invert(tests[i], 0, 0));
    if (invert(tests[i], 0, 1) != expected[i][0])
      printf("Test %d failed: expected 0x%x, got 0x%x\n", i, expected[i][0], invert(tests[i], 0, 1));
    if (invert(tests[i], 3, 3) != expected[i][1])
      printf("Test %d failed: expected 0x%x, got 0x%x\n", i, expected[i][1], invert(tests[i], 3, 3));
  }
}

unsigned invert(unsigned x, int p, int n) {
  unsigned inverted_bits = ~ getbits(x, p, n);
  return setbits(x, p, n, inverted_bits);
}

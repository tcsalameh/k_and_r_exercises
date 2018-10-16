/* In a two's complement number system,
 * x &= (x-1) deletes the rightmost 1-bit in x.
 * Explain why. Use this observation to write a
 * faster version of bitcount */

/* Why:
 * Suppose x is odd. Then, the trailing bit
 * of x-1 is 0 while all the other bits are the same.
 * If you & x with itself, you get x. If you & it
 * with a near copy that has the trailing bit as 0,
 * you get x but with the last bit set to 0 (deleting it).
 *
 * Suppose x is even. Then, x-1 will set all the bits right
 * of the rightmost 1 bit to 1, and set the rightmost 1 bit to 0.
 * If you & x with x but with the rightmost 1 bit flipped to 0 and
 * all the bits right of it flipped to 1, it will set the rightmost 1 bit
 * to 0. */
#include <stdio.h>

int bitcount(unsigned x);

int main()
{
  unsigned tests[] = {0x0, 0xd, 0x29, 0x1f, 0x3bb};
                /* {0, 1101, 101001, 11111, 1110111011} */
  int expected[] = {0, 3, 3, 5, 8};

  for (int i=0; i<5; i++) {
    if (bitcount(tests[i]) != expected[i])
      printf("Test %d failed: expected %d for bitcount(0x%x), got %d\n", i, expected[i], tests[i], bitcount(tests[i]));
    else
      printf("Test %d passed\n", i);
  }
}

int bitcount(unsigned x)
{
  int b;

  for (b=0; x!=0; x &= (x-1))
    b++;
  return b;
}

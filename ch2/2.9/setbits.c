/* Write a function setbits(x, p, n, y) that returns
 * x with the n bits that begin at position p set
 * to the rightmost n bits of y, leaving the other bits
 * unchanged */
#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned getbits(unsigned x, int p, int n);

int main()
{
  unsigned testsx[] = {0x0, 0xd, 0x29, 0x1f, 0x3bb};
                       /* {0, 1101, 101001, 11111, 1110111011} */
  unsigned testsy[] = {0x6, 0x3, 0xa, 0x0, 0x7fe};
                       /* {110, 11, 1010, 0, 11111111110} */

  unsigned testa = setbits(testsx[0], 2, 3, testsy[0]);
  unsigned testb = setbits(testsx[1], 2, 1, testsy[1]);
  unsigned testc = setbits(testsx[2], 3, 1, testsy[2]);
  unsigned testd = setbits(testsx[3], 6, 5, testsy[3]);
  unsigned teste = setbits(testsx[4], 6, 5, testsy[4]);
  unsigned testf = setbits(testsx[2], 0, 0, testsy[2]);

  // 3 bits that begin at position 2: 000
  // rightmost 3 bits of y: 110
  // outcome: 110
  unsigned expecteda = 0x6;
  // 1 bit that begins at position 2: 1
  // rightmost 1 bit of y: 1
  // outcome: unchanged
  unsigned expectedb = 0xd;
  // 1 bit that begins at pos 3: 1
  // rightmost single bit of y: 0
  // outcome: 100001
  unsigned expectedc = 0x21;
  // 5 bits that begin at pos 6: 00111
  // rightmost 5 bits of y: 00000
  // outcome: 0000011
  unsigned expectedd = 0x3;
  // 5 bits that begin as pos 6: 01110
  // rightmost 5 bits of y: 11110
  // outcome: 1111111011
  unsigned expectede = 0x3fb;
  // no change, since we start at 0 and change nothing
  unsigned expectedf = 0x29;


  printf("Test case A: Expected 0x%x, got 0x%x\n", expecteda, testa);
  printf("Test case B: Expected 0x%x, got 0x%x\n", expectedb, testb);
  printf("Test case C: Expected 0x%x, got 0x%x\n", expectedc, testc);
  printf("Test case D: Expected 0x%x, got 0x%x\n", expectedd, testd);
  printf("Test case E: Expected 0x%x, got 0x%x\n", expectede, teste);
  printf("Test case F: Expected 0x%x, got 0x%x\n", expectedf, testf);

}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
	unsigned left_x = (x >> (p+1)) << (p+1);
  unsigned y_mask = (y & ~(~ 0 << n)) << (p-n+1);
	unsigned right_x = getbits(x, p-n, p-n+1);

	return right_x | y_mask | left_x;
}

unsigned getbits(unsigned x, int p, int n) {
  return (x >> (p+1-n)) & ~(~ 0 << n);
}

unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned getbits(unsigned x, int p, int n);

unsigned setbits(unsigned x, int p, int n, unsigned y) {
	unsigned left_x = (x >> (p+1)) << (p+1);
  unsigned y_mask = (y & ~(~ 0 << n)) << (p-n+1);
	unsigned right_x = getbits(x, p-n, p-n+1);

	return right_x | y_mask | left_x;
}

unsigned getbits(unsigned x, int p, int n) {
  return (x >> (p+1-n)) & ~(~ 0 << n);
}

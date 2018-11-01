#include <stdio.h>

void printd(int n);

int main()
{
  printd(5498);
  printf("\n");
  printd(-55);
  printf("\n");
}

/* printd: print n in decimal */
void printd(int n)
{
  if (n < 0) {
    putchar('-');
    n = -n;
  }
  if (n / 10) /* n/10 non-zero */
    printd(n / 10);
  putchar(n % 10 + '0');
}

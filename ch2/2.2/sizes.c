#include <stdio.h>
#include <limits.h>

/* Print ranges of char, short, int, long, singed/unsigned */
int main()
{
  // from header files
  printf("Signed char range: %d to %d\n", CHAR_MIN, CHAR_MAX);
  printf("Unsigned char range: 0 to %u\n", UCHAR_MAX);
  printf("Signed int range: %d to %d\n", INT_MIN, INT_MAX);
  printf("Unsigned int range: 0 to %u\n", UINT_MAX);
  printf("Signed short range: %d to %d\n", SHRT_MIN, SHRT_MAX);
  printf("Unsigned short range: 0 to %u\n", USHRT_MAX);
  printf("Signed long range: %ld to %ld\n", LONG_MIN, LONG_MAX);
  printf("Unsigned long range: 0 to %lu\n", ULONG_MAX);
  printf("\n");

  // by direct computation
  char char_max, char_min;
  unsigned char uchar_max;
  int int_min, int_max;
  unsigned int uint_max;
  short shrt_min, shrt_max;
  unsigned short ushrt_max;
  long long_min, long_max;
  unsigned long ulong_max;

  uchar_max = 0;
  --uchar_max;

  char_max = uchar_max / 2;
  char_min = char_max + 1;

  uint_max = 0;
  --uint_max;

  int_max = uint_max / 2;
  int_min = int_max + 1;

  ushrt_max = 0;
  --ushrt_max;

  shrt_max = ushrt_max / 2;
  shrt_min = shrt_max + 1;

  ulong_max = 0;
  --ulong_max;

  long_max = ulong_max / 2;
  long_min = long_max + 1;

  printf("Signed char range: %d to %d\n", char_min, char_max);
  printf("Unsigned char range: 0 to %u\n", uchar_max);
  printf("Signed int range: %d to %d\n", int_min, int_max);
  printf("Unsigned int range: 0 to %u\n", uint_max);
  printf("Signed short range: %d to %d\n", shrt_min, shrt_max);
  printf("Unsigned short range: 0 to %u\n", ushrt_max);
  printf("Signed long range: %ld to %ld\n", long_min, long_max);
  printf("Unsigned long range: 0 to %lu\n", ulong_max);

}



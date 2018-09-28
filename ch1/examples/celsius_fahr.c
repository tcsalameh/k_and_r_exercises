#include <stdio.h>

/* print Celsius-Farenheit table
 * for fahr = 0, 20, ..., 300 */

main()
{
  float fahr, celsius;
  int lower, upper, step;

  lower = 0;     /* lower limit of temp table */
  upper = 150;   /* upper limit of temp table */
  step = 10;     /* step size */

  celsius = lower;
  printf("%3s %6s\n", "C", "F");
  while (celsius <= upper) {
    fahr = celsius * (9.0/5.0) + 32.0;
    printf("%3.0f %6.1f\n", celsius, fahr);
    celsius = celsius + step;
  }
}

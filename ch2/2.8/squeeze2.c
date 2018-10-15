/* Write an alternate version of squeeze(s1, s2) that
 * deletes each character in s1 that matches any char.
 * in s2 */
#include <stdio.h>
#include "util.h"

void squeeze_plus(char s1[], char s2[]);

int main() {
  char tests[][50] = {"abcd", "some string", "another string", "*123 r*9]rd[ r^&*i@*"};
  char expected[][50] = {"abcd", "some stng", "anothe stng", "123 9d[ ^&@"};
  char squeezer[] = "ir]*";

  for (int i=0; i<4; i++) {
    squeeze_plus(tests[i], squeezer);
    if (strequal(tests[i], expected[i]))
      printf("Test %d passed.\n", i);
    else
      printf("Test %d failed. Expected %s, got %s.\n", i, expected[i], tests[i]);
  }
}

void squeeze_plus(char s1[], char s2[]) {
  int i, j;

  for (i = j = 0; s1[i] != '\0'; i++) {
    if (!strcontains(s2, s1[i]))
      s1[j++] = s1[i];
  }

  s1[j] = '\0';
}

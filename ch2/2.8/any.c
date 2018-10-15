/* Write the function any(s1, s2) which returns the first
 * location in the string s1 where any character from the
 * string s2 occurs, or -1 if s1 contains no chars
 * from s2 (essentially replicating `strpbrk`)*/
#include <stdio.h>
#include "util.h"

int any(char[], char[]);

int main()
{
  char tests[][50] = {"", "foobar.", "123 alb rd."};
  int expected[] = {
    -1, // tests[0], tests[0]
    -1, // tests[0], tests[1]
    -1, // tests[0], tests[2]
    -1, // tests[1], tests[0]
    0, // tests[1], tests[1]
    3, // tests[1], tests[2]
    -1, // tests[2], tests[0]
    4, // tests[2], tests[1]
    0 // tests[2], tests[2]
  };
  int result;

  for (int i=0; i<3; i++) {
    for (int j=0; j<3; j++) {
      result = any(tests[i], tests[j]);
      if (result == expected[i*3+j])
        printf("Test %d passed.\n", i*3+j);
      else
        printf("Test %d failed. Expected %d for any(%s, %s), got %d.\n", i*3+j, expected[i*3+j], tests[i], tests[j], result);
    }
  }
}

int any(char s1[], char s2[]) {
  for (int i=0; s1[i] != '\0'; i++) {
    if (strcontains(s2, s1[i])) {
      return i;
    }
  }

  return -1;
}

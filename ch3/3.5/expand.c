/* Write a function expand(s1, s2) that expands
 * shorthand notations like a-z in the string s1
 * into the equivalent complete list abc...xyz in
 * s2. Allow for letters of either case and digits,
 * and be prepared to handle cases like a-b-c and
 * a-z0-9 and -a-z. Arrange that a leading or trailing -
 * is taken literally */
#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000    /* Max length of output string */

void expand(char s1[], char s2[]);
int expandable(int i, char s1[]);
int valid_char_combo(char c1, char c2);

int main()
{
  char expanded[MAX_LEN];

  char test[][100] = {
    "",
    "a-f",
    "-0-8B-Z",
    "a-g-z something a-8- e-a"
  };

  char expected[][100] = {
    "",
    "abcdef",
    "-012345678BCDEFGHIJKLMNOPQRSTUVWXYZ",
    "abcdefghijklmnopqrstuvwxyz something a-8- e-a"
  };

  for (int i=0; i<4; i++) {
    expand(test[i], expanded);
    if (strcmp(expanded, expected[i]))
      printf("Expected %s for expand(%s, s2); got %s\n", expected[i], test[i], expanded);
    else
      printf("Test %d passed!\n", i);
    for (int j=0; j < MAX_LEN; j++)
      expanded[j] = '.';
  }
}

int expandable(int i, char s1[]) {
  return (
      s1[i] == '-' &&
      i > 0 &&
      i < strlen(s1) - 1 &&
      valid_char_combo(s1[i-1], s1[i+1]) &&
      s1[i+1] > s1[i-1]
  );
}

int valid_char_combo(char c1, char c2) {
  if (c1 >= 'a' && c1 <= 'z')
    return (c2 >= 'a' && c2 <= 'z');
  if (c1 >= 'A' && c1 <= 'Z')
    return (c2 >= 'A' && c2 <= 'Z');
  if (c1 >= '0' && c1 <= '9')
    return (c2 >= '0' && c2 <= '9');
  return 1;
}

void expand(char s1[], char s2[])
{
  int i, j, c_start, c_end;
  for (i = 0, j = 0; i < strlen(s1); i++) {
    if (expandable(i, s1)) {
      for (c_start = s1[i-1] + 1, c_end = s1[i+1]; c_start < c_end; c_start++, j++)
        s2[j] = c_start;
    } else {
      s2[j] = s1[i];
      j++;
    }
  }

  s2[j] = '\0';
}

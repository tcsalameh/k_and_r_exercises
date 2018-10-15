/* Write the function htoi(s), which converts a string
 * of hexadecimal digits (including optional 0x or 0X)
 * into its equivalent integer value. The allowable digits
 * are 0-9, a-f, A-F */
#include <stdio.h>
#include <ctype.h>

int htoi(char s[]);

int main() {
  char tests[][10] = {"0x0", "0x19", "0Xa3f", "0xB7", "0x726eC4", "af"};
  int expects[] = {0, 25, 2623, 183, 7499460, 175};
  int result;

  for (int i=0; i < 6; ++i) {
    result = htoi(tests[i]);
    if (result == expects[i])
      printf("Test %d passed.\n", i);
    else
      printf("Test %d failed. Expected %d for %s, got %d.\n", i, expects[i], tests[i], result);
  }
}

int htoi(char s[]) {
  int c, tmp;
  int result = 0;

  for (int i=0; s[i]!='\0'; ++i) {
    c = tolower(s[i]);
    if (i == 0 && c == '0' || c == 'x') {
      continue;
    } else {
      if (isdigit(c))
        tmp = c - '0';
      else
        tmp = c - 'a' + 10;

      result = 16*result + tmp;
    }
  }
  return result;
}

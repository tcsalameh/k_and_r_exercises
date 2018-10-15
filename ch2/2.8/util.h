#include <ctype.h>

int strequal(char s1[], char s2[]);
int strcontains(char s[], char c);

int strcontains(char s[], char c) {
  for (int k=0; s[k] != '\0'; ++k) {
    if (s[k] == c)
      return 1;
  }

  return 0;
}

int strequal(char s1[], char s2[]) {
  int i;

  for (i=0; s1[i]!='\0' && s2[i]!='\0'; i++) {
    if (s1[i] != s2[i])
      return 0;
  }

  if (s1[i] != s2[i]) {
    return 0;
  } else {
    return 1;
  }
}

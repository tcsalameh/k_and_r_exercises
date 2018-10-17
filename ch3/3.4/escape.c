/* Write a function escape(s, t) that converts
 * characters like newline and tab into visible
 * escape sequences like \n and \t as it copies
 * the string t to s. Use a switch. Write a function
 * for the other direction as well, converting escape
 * sequences into real characters. */
#include <stdio.h>

#define MAX_LEN 100    /* max string length we'll operate on */
#define IN      0      /* inside an escape sequence */
#define OUT     1      /* outside an escape sequence */

void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int strequal(char s1[], char s2[]);

int main()
{
  char s[MAX_LEN];

  char tests[][MAX_LEN] = {
    "",
    "hello",
    "this is a newline\n",
    "\t\tindented line",
    "\\t to test \\n",
    "\a\b\f\n\r\t\v",
    "\\a\\b\\f\\n\\r\\t\\v"
  };

  char esc_expected[][MAX_LEN] = {
    "",
    "hello",
    "this is a newline\\n",
    "\\t\\tindented line",
    "\\t to test \\n",
    "\\a\\b\\f\\n\\r\\t\\v",
    "\\a\\b\\f\\n\\r\\t\\v"
  };

  char unesc_expected[][MAX_LEN] = {
    "",
    "hello",
    "this is a newline\n",
    "\t\tindented line",
    "\t to test \n",
    "\a\b\f\n\r\t\v",
    "\a\b\f\n\r\t\v"
  };

  for (int i; i<7; i++) {
    for (int j=0; j<MAX_LEN; j++)
      s[j] = '.';

    escape(s, tests[i]);
    if (!strequal(s, esc_expected[i]))
      printf("Got '%s' for escape(s, '%s'), expected '%s'\n\n", s, tests[i], esc_expected[i]);

    for (int j=0; j<MAX_LEN; j++)
      s[j] = '.';

    unescape(s, esc_expected[i]);
    if (!strequal(s, unesc_expected[i]))
      printf("Got '%s' for unescape(s, '%s'), expected '%s'\n\n", s, esc_expected[i], unesc_expected[i]);
  }
}

void escape(char s[], char t[])
{
  int i, j;
  i = j = 0;
  while (t[i] != '\0' && i < MAX_LEN && j < MAX_LEN) {
    switch (t[i]) {
      case '\a':
        s[j] = '\\';
        j++;
        s[j] = 'a';
        break;
      case '\b':
        s[j] = '\\';
        j++;
        s[j] = 'b';
        break;
      case '\f':
        s[j] = '\\';
        j++;
        s[j] = 'f';
        break;
      case '\n':
        s[j] = '\\';
        j++;
        s[j] = 'n';
        break;
      case '\r':
        s[j] = '\\';
        j++;
        s[j] = 'r';
        break;
      case '\t':
        s[j] = '\\';
        j++;
        s[j] = 't';
        break;
      case '\v':
        s[j] = '\\';
        j++;
        s[j] = 'v';
        break;
      default:
        s[j] = t[i];
        break;
    }
    i++;
    j++;
  }
  s[j] = '\0';
}

void unescape(char s[], char t[])
{
  int i, j, state;
  i = j = 0;
  state = OUT;
  while (t[i] != '\0' && i < MAX_LEN && j < MAX_LEN) {
    switch (t[i]) {
      case '\\':
        state = IN;
        i++;
        break;
      case 'a':
        if (state == IN) {
          s[j] = '\a';
          state = OUT;
          i++;
          j++;
          break;
        }
      case 'b':
        if (state == IN) {
          s[j] = '\b';
          state = OUT;
          i++;
          j++;
          break;
        }
      case 'f':
        if (state == IN) {
          s[j] = '\f';
          state = OUT;
          i++;
          j++;
          break;
        }
      case 'n':
        if (state == IN) {
          s[j] = '\n';
          state = OUT;
          i++;
          j++;
          break;
        }
      case 'r':
        if (state == IN) {
          s[j] = '\r';
          state = OUT;
          i++;
          j++;
          break;
        }
      case 't':
        if (state == IN) {
          s[j] = '\t';
          state = OUT;
          i++;
          j++;
          break;
        }
      case 'v':
        if (state == IN) {
          s[j] = '\v';
          state = OUT;
          i++;
          j++;
          break;
        }
      default:
        s[j] = t[i];
        state = OUT;
        i++;
        j++;
        break;
    }
  }
  s[j] = '\0';
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

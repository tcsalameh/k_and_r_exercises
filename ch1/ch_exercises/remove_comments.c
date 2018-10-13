#include <stdio.h>

#define IN    0    /* Whether we are in a comment or quote string */
#define OUT   1    /* Whether we are outside of a comment or quote string */

// Remove comments from a C program
int main()
{
  int c;  // current character
  int c2; // second character, to record two-char sequences
  int m_comment_state, s_comment_state, quote_state; // multi-line comments, single line comments, and quote strings

  m_comment_state = s_comment_state = quote_state = OUT;

  while ((c = getchar()) != EOF) {
    if (c == '\n' && s_comment_state == IN) {
      s_comment_state = OUT;
    }
    if (c == '"') {
      if (s_comment_state != IN && m_comment_state != IN) {
        if (quote_state == IN) {
          quote_state == OUT;
        } else {
          quote_state == IN;
        }
      }
    }
    if (c == '/') {
      if (quote_state != IN) {
        // TODO: What if this is EOF?
        c2 = getchar();
        if (c2 == '/') {
          s_comment_state = IN;
        } else if (c2 == '*') {
          m_comment_state = IN;
        } else {
          printf("%c", c);
          printf("%c", c2);
          continue;
        }
      }
    }
    if (c == '*') {
      if (quote_state != IN) {
        // TODO: What if this is EOF?
        c2 = getchar();
        if (c2 == '/') {
          m_comment_state = OUT;
        } else {
          printf("%c", c);
          printf("%c", c2);
        }
        continue;
      }
    }
    if (m_comment_state == OUT && s_comment_state == OUT) {
      printf("%c", c);
    }
  }
}

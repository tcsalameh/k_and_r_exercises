#include <stdio.h>

#define IN       0    /* Whether we are in a comment or quote string */
#define OUT      1    /* Whether we are outside of a comment or quote string */
#define MAX_SIZE 100000 /* Max number of chars we allow for the input */

int removeComments(char program[], int max_size);

int removeComments(char program[], int max_size) {
  int c, c2, i; // track current character, next, and index

  int m_comment_state, s_comment_state, quote_state; // multi-line comments, single line comments, and quote strings

  m_comment_state = s_comment_state = quote_state = OUT;

  i = 0;

  while ((c = getchar()) != EOF && i < MAX_SIZE) {
    if (c == '\n' && s_comment_state == IN) {
      s_comment_state = OUT;
    }
    if (c == '"') {
      if (s_comment_state == OUT && m_comment_state == OUT) {
        if (i == 0 || program[i-1] != '\'') {
          if (quote_state == IN) {
            quote_state == OUT;
          } else {
            quote_state == IN;
          }
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
          program[i] = c;
          ++i;
          program[i] = c2;
          ++i;
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
          program[i] = c;
          ++i;
          program[i] = c2;
          ++i;
        }
        continue;
      }
    }
    if (m_comment_state == OUT && s_comment_state == OUT) {
      program[i] = c;
      ++i;
    }
  }

  return i;
}

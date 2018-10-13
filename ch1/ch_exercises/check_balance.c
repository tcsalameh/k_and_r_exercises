#include <stdio.h>
#include "remove_comments.h"


/* Checks whether parens, brackets, and braces are unbalanced in a C program */
int main()
{
  int len, paren_stack, bracket_stack, brace_stack, c, quote;
  char program[MAX_SIZE];

  len = removeComments(program, MAX_SIZE);
  quote = OUT;
  paren_stack = bracket_stack = brace_stack = 0;

  for (int i=0; i<len; ++i) {
    c = program[i];
    if (c == '"') {
      if (i == 0 || program[i-1] != '\'') {
        if (quote == OUT) {
          quote = IN;
        } else {
          quote = OUT;
        }
      }
    }
    if (quote == OUT) {
      if (c == '(')
        ++paren_stack;
      if (c == ')')
        --paren_stack;
      if (c == '[')
        ++bracket_stack;
      if (c == ']')
        --bracket_stack;
      if (c == '{')
        ++brace_stack;
      if (c == '}')
        --brace_stack;
    }
  }


  if (paren_stack != 0)
    printf("ERROR: (Parens are not balanced!\n");
  if (bracket_stack != 0)
    printf("ERROR: [Brackets are not balanced!\n");
  if (brace_stack != 0)
    printf("ERROR: {Braces are not balanced!\n");

  if (paren_stack == 0 && bracket_stack == 0 && brace_stack ==0)
    printf("Parens, brackets, and braces are all balanced.\n");
}

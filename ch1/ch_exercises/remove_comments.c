#include <stdio.h>
#include "remove_comments.h"

// Remove comments from a C program
int main()
{
  char program[MAX_SIZE];

  printf("%s", removeComments(program, MAX_SIZE));
}

/* undcl: convert word descs to declaration */
/* 5-19: Modify undcl so that it does not add
 * redundant parentheses to declarations */
#include <stdio.h>
#include "token.h"

char err[1000];          /* store error messages */
char out[1000];          /* output string */

int main()
{
  int type;
  char temp[MAXTOKEN];

  while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n')
      if (type == PARENS || type == BRACKETS)
        strcat(out, token);
      else if (type == '*') {
        sprintf(temp, "(*%s)", out);
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else
        printf("invalid input at %s\n", token);
    printf("%s\n", out);
  }
  return 0;
}

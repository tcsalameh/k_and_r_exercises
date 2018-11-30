#include <string.h>
#include <ctype.h>
#include "getch.h"

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

int tokentype;           /* type of last token */
int gettoken(void);
char token[MAXTOKEN];    /* last token string */
char datatype[MAXTOKEN]; /* data type = char, int, etc */

int gettoken(void) {
  int c, getch(void);
  void ungetch(int);
  char *p = token;

  while ((c = getch()) == ' ' || c == '\t')
    ;
  if (c == '(') {
    if ((c = getch()) == ')') {
      strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = '(';
    }
  } else if (c == '[') {
     for (*p++ = c; (*p++ = getch()) != ']'; )
       ;
     *p = '\0';
     return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = c; isalnum(c = getch()); )
      *p++ = c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else
    return tokentype = c;
}

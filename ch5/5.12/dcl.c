/* 5-18: Make dcl recover from input errors. */
/* 5-19: Modify undcl so that it does not add
 * redundant parentheses to declarations */
/* 5-20: Expand dcl to handle declarations with
 * function argument types, qualifiers like const,
 * and so on. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "getch.h"

#define MAXTOKEN 100
#define RED      "\033[31m"
#define CLEAR    "\033[0m"

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc */
char err[1000];          /* store error messages */
char out[1000];          /* output string */

/* convert declaration to words */
int main()
{
  int lineno = 0;

  strcpy(err, "syntax error");
  while (gettoken() != EOF) {  /* 1st token on line */
    strcpy(datatype, token);   /* is the datatype */
    out[0] = '\0';
    dcl();     /* parse rest of line */
    if (tokentype != '\n') {
      printf("%serror at line %d: %s%s\n", RED, lineno, err, CLEAR);
      while (tokentype != '\n')
        gettoken();
    } else
      printf("%s: %s %s\n", name, out, datatype);
    lineno++;
    strcpy(err, "syntax error");
  }
  return 0;
}

/* dcl: parse a declarator */
void dcl(void)
{
  int ns;

  for (ns = 0; gettoken() == '*';) /* count *'s */
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
  int type;

  if (tokentype == '(') {    /* ( dcl ) */
    dcl();
    if (tokentype != ')') {
      strcpy(err, "missing )");
    }
  } else if (tokentype == NAME)    /* var name */
      strcpy(name, token);
  else
    strcpy(err, "expected name or (dcl)");

  while ((type=gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS)
      strcat(out, " function returning");
    else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
}

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

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "getch.h"

#define MAXWORD 100
#define NKEYS   (sizeof keytab / sizeof keytab[0])
#define IN      0
#define OUT     1

struct key {
  char *word;
  int count;
} keytab[] = {
  "auto", 0,
  "break", 0,
  "case", 0,
  "char", 0,
  "const", 0,
  "continue", 0,
  "default", 0,
  "do", 0,
  "double", 0,
  "else", 0,
  "enum", 0,
  "extern", 0,
  "float", 0,
  "for", 0,
  "goto", 0,
  "if", 0,
  "int", 0,
  "long", 0,
  "register", 0,
  "return", 0,
  "short", 0,
  "signed", 0,
  "sizeof", 0,
  "static", 0,
  "struct", 0,
  "switch", 0,
  "typedef", 0,
  "union", 0,
  "unsigned", 0,
  "void", 0,
  "volatile", 0,
  "while", 0
};

int comment = OUT;

int getword(char *, int);
struct key *binsearch(char *, struct key *, int);

/* count C keywords, pointer version */
int main()
{
  char word[MAXWORD];
  struct key *p;

  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      if ((p=binsearch(word, keytab, NKEYS)) != NULL)
        p->count++;
  for (p = keytab; p < keytab + NKEYS; p++)
    if (p->count > 0)
      printf("%4d %s\n", p->count, p->word);
  return 0;
}

/* binsearch: find word in tab[0]..tab[n-1] */
struct key *binsearch(char *word, struct key *tab, int n)
{
  int cond;
  struct key *low = &tab[0];
  struct key *high = &tab[n];
  struct key *mid;

  while (low < high) {
    mid = low + (high-low) / 2;
    if ((cond = strcmp(word, mid->word)) < 0)
      high = mid;
    else if (cond > 0)
      low = mid + 1;
    else
      return mid;
  }

  return NULL;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  while (isspace(c = getch()))
    ;

  if (c == '/') {
    if ((c = getch()) == '*')
      comment = IN;
  } else if (c == '*' && comment == IN) {
    if ((c = getch()) == '/') {
      comment = OUT;
      return c;
    }
  } else if (c == '"') {
    while ((c = getch()) != '"' && c != '\'')
      ;
    return c;
  }

  if (comment == IN)
    return c;

  if (c != EOF)
    *w++ = c;
  if (!isalpha(c) && c != '#' && c != '_') {
    *w = '\0';
    return c;
  }
  for ( ; --lim > 0; w++)
    if (!isalnum(*w = getch()) && *w != '#' && *w != '_') {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

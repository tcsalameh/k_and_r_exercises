#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>  /* for atof() */
#include <math.h>
#include <string.h>

#define MAXOP    100  /* max size of operand or operator */
#define NUMBER   '0'  /* signal that a number was found */
#define VARIABLE '1'  /* signal that a variable was found */
#define MAXVAL   100  /* max size of val stack */
#define MAXLINE  1000 /* max line length */
#define BUFSIZE  100  /* character input buffer */
#define NVARS    26   /* number of variables */

int sp = 0;                   /* next free stack position */
double val[MAXVAL];           /* value stack */
double vars[NVARS];           /* variable values */
double varsetflags[NVARS];    /* variable set? */
char lastprintvar = 'z';      /* var holding value of last print */
char line[MAXLINE];
char lnptr;
int len;

int getop(char []);
void push(double);
double pop(void);
void setvar(char, double);
double getvar(char);
void clearvars(void);
int isset(char);
int getLine(char [], int);

/* reverse polish notation */
int main()
{
  int type;
  double op2;
  double op1;
  char s[MAXOP];

  while ((len = getLine(line, MAXLINE)) != 0) {
    for (lnptr = 0; lnptr < len;) {
      type = getop(s);
      switch (type) {
        case NUMBER:
          push(atof(s));
          break;
        case VARIABLE:
          if (isset(s[0])) {
            push(getvar(s[0]));
          }
          else {
            push(s[0]);
          }
          break;
        case '+':
          push(pop() + pop());
          break;
        case '*':
          push(pop() * pop());
          break;
        case '-':
          op2 = pop();
          push(pop() - op2);
          break;
        case '/':
          op2 = pop();
          if (op2 != 0.0)
            push(pop() / op2);
          else
            printf("error: zero divisor\n");
          break;
        case '%':
          op2 = pop();
          if (op2 != 0.0)
            push((int) pop() % (int) op2);
          else
            printf("error: zero divisor\n");
          break;
        case '=': /* variable assignment */
          op2 = pop();
          if ((op1 = pop()) == lastprintvar)
            printf("error: %c is a reserved variable\n", lastprintvar);
          else
            setvar(op1, op2);
          break;
        case '~': /* sin */
          push(sin(pop()));
          break;
        case '^': /* pow */
          op2 = pop();
          push(pow(pop(), op2));
          break;
        case '>': /* exp */
          push(exp(pop()));
          break;
        case '<': /* log */
          push(log(pop()));
          break;
        case '?': /* sqrt */
          push(sqrt(pop()));
          break;
        case '@': /* print top stack element */
          op1 = pop();
          printf("top stack element: %.8g\n", op1);
          push(op1);
          break;
        case ':': /* duplicate the top stack element */
          op1 = pop();
          push(op1);
          push(op1);
          break;
        case '&': /* swap top two stack elems */
          op2 = pop();
          op1 = pop();
          push(op2);
          push(op1);
          break;
        case '_': /* clear the stack */
          sp = 0;
          val[sp] = 0.0;
          break;
        case '\n':
          clearvars();
          setvar(lastprintvar, pop());
          printf("\t%.8g\n", getvar(lastprintvar));
          break;
        default:
          printf("error: unknown command %s\n", s);
          break;
      }
    }
  }
  return 0;
}

/* push: push f onto value stack */
void push(double f)
{
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
  int i, c;

  while ((s[0] = c = line[lnptr++]) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (c >= 'a' && c <= 'z') {
    s[0] = c;
    return VARIABLE;
  }
  if (!isdigit(c) && c != '.' && c != '-')
    return c;

  if (c == '-') {
    if (isdigit(c = line[lnptr++])) {
      lnptr--;
      c = '-';
    } else {
      lnptr--;
      return '-';
    }
  }

  i = 0;
  if (isdigit(c) || c == '-')
    while (isdigit(s[++i] = c = line[lnptr++]))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = line[lnptr++]))
      ;
  s[i] = '\0';
  if (c != EOF)
    lnptr--;
  return NUMBER;
}

int getLine(char line[], int limit)
{
  int c, i;

  for (i=0; (i < limit-1) && (c=getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;

  if (c == '\n') {
    line[i] = c;
    ++i;
  }
  line[i] = '\0';
  return i;
}

void setvar(char var, double val)
{
  vars[var - 'a'] = val;
  varsetflags[var - 'a'] = 1;
}

double getvar(char var)
{
  return vars[var - 'a'];
}

int isset(char var)
{
  return varsetflags[var - 'a'];
}

void clearvars(void)
{
  for (int i=0; i<NVARS; i++) {
    vars[i] = 0;
    varsetflags[i] = 0;
  }
}

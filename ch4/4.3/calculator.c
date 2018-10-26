#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>  /* for atof() */
#include <math.h>

#define MAXOP    100  /* max size of operand or operator */
#define NUMBER   '0'  /* signal that a number was found */
#define MAXVAL   100  /* max size of val stack */
#define BUFSIZE  100  /* character input buffer */

int sp = 0;           /* next free stack position */
double val[MAXVAL];   /* value stack */
char buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;         /* pointer to next free pos in buf */

int getch(void);
void ungetch(int);
int getop(char []);
void push(double);
double pop(void);

/* reverse polish notation */
int main()
{
  int type;
  double op2;
  double op1;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
      case NUMBER:
        push(atof(s));
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
        printf("\t%.8g\n", pop());
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
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

  while ((s[0] = c = getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-')
    return c;

  if (c == '-') {
    if (isdigit(c = getch())) {
      ungetch(c);
      c = '-';
    } else {
      ungetch(c);
      return '-';
    }
  }

  i = 0;
  if (isdigit(c) || c == '-')
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.')
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

/* get a (possibley pushed back) character */
int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push a character back on input */
void ungetch(int c)
{
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

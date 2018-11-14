/* Write the program expr, which evaluates a reverse Polish expression from the command line,
 * where each operator or operand is a separate argument, For example,
 *      expr 2 3 4 + *
 * evaluates to 2 X (3 + 4) */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>  /* for atof() */

#define MAXOP    100  /* max size of operand or operator */
#define MAXVAL   100  /* max size of val stack */
#define NUMBER   '0'  /* signal that a number was found */

int sp = 0;                   /* next free stack position */
double val[MAXVAL];           /* value stack */

int getop(char []);
void push(double);
double pop(void);

/* reverse polish notation */
int main(int argc, char *argv[])
{
  int type;
  double op2;
  double op1;

  while (--argc > 0) {
    type = getop(*++argv);
    switch (type) {
      case NUMBER:
        push(atof(*argv));
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
      default:
        printf("error: unknown command %s\n", *argv);
        break;
    }
  }
  printf("\t%.8g\n", pop());
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
int getop(char arg[])
{
  int i, dec_count;

  i = 0;

  if (!isdigit(arg[i]) && arg[i] != '.' && arg[i] != '-')
    return arg[i];

  if (arg[i] == '-') {
    if (!isdigit(arg[i+1])) {
      return '-';
    } else {
      i++;
    }
  }

  dec_count = 0;
  for (i = 0; arg[i] != '\0'; i++) {
    if (!isdigit(arg[i])) {
      if (arg[i] == '.' && dec_count == 0)
        dec_count++;
      else
        return '?';
    }
  }
  return NUMBER;
}

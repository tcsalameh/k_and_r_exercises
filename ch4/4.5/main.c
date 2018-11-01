#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calc.h"

#define MAXOP        100
#define LASTPRINTVAR 'z'  /* var holding value of last print */

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
        if ((op1 = pop()) == LASTPRINTVAR)
          printf("error: %c is a reserved variable\n", LASTPRINTVAR);
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
        clearstack();
        break;
      case '\n':
        clearvars();
        setvar(LASTPRINTVAR, pop());
        printf("\t%.8g\n", getvar(LASTPRINTVAR));
        break;
      default:
        printf("error: unknown command %s\n", s);
        break;
    }
  }
  return 0;

}

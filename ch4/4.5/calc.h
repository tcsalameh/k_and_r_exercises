#define NUMBER   '0'  /* signal that a number was found */
#define VARIABLE '1'  /* signal that a variable was found */

void push(double);
double pop(void);
void clearstack(void);
int getop(char []);
int getch(void);
void ungetch(int);
void setvar(char, double);
double getvar(char);
void clearvars(void);
int isset(char);

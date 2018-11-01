#include <stdio.h>
#include <string.h>

#define QMAX 1000    /* Max queue size we can accept */

void itoa(int, int, char []);
void qpush(int);
int qpop(void);
int qpeek(void);

int queue[QMAX];
int qstart = 0;
int qend = 0;

int main()
{
  char s[20];
  int test[] = { 0, 1, 58, -124, 1091 };
  char expected[][20] = { "0", "1", "58", "-124", "1091" };

  for (int i = 0; i < 5; i++) {
    itoa(test[i], 0, s);
    if (strcmp(s, expected[i]))
      printf("Expected %s for itoa(%d, 0, s), got %s\n", expected[i], test[i], s);
  }
}

/* itoa: convert n to chars in s */
void itoa(int n, int i, char s[])
{
  if (n < 0) {
    s[i++] = '-';
    n = -n;
  }
  qpush(n % 10 + '0');
  if (n / 10)
    itoa(n / 10, i+1, s);
  s[i] = qpop();
  if (n < 10)
    s[++i] = '\0';
}

void qpush(int c)
{
  if (qend >= QMAX) {
    printf("error: queue full");
    return;
  }

  queue[qend++] = c;
}

int qpop(void)
{
  if (qstart == qend) {
    if (qend >= QMAX)
      qstart = qend = 0;
    printf("error: queue empty");
    return queue[qstart];
  }
  return queue[qstart++];
}

int qpeek(void)
{
  return queue[qstart];
}

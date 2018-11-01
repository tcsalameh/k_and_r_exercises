#include <stdio.h>

#define NVARS        26   /* number of variables */

static double vars[NVARS];           /* variable values */
static double varsetflags[NVARS];    /* variable set? */

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

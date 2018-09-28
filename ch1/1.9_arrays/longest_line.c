#include <stdio.h>
#define MAXLINE 1000      /* max line length we expect */

// while (there's another line)
//   if (it's longer than the prev longest)
//     save it
//     save its length
// print longest line

int getLine(char line[], int maxline);
void copy(char to[], char from[]);

main()
{
  int len;     /* current line length */
  int max;     /* max observed so far */
  char line[MAXLINE];      /* current line */
  char longest[MAXLINE];   /* longest line so far */

  max = 0;
  while ((len = getLine(line, MAXLINE)) > 0)
    if (len > max) {
      max = len;
      copy(longest, line);
    }
  if (max > 0) {
    printf("%s", longest);
    printf("\n");
    printf("%d", max);
    printf("\n");
  }
  return 0;
}

int getLine(char s[], int lim)
{
  int c, i, j;

  for (i=0; (c=getchar()) != EOF && c!= '\n'; ++i) {
    if (i < lim-1) {
      s[i] = c;
      j = i;
    }
  }
  if (c == '\n') {
    s[j] = c;
    ++j;
  }
  s[j]= '\0';
  return i;
}

void copy(char to[], char from[])
{
  int i;
  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}

#include <stdio.h>

#define IN  1    /* in a word */
#define OUT 0    /* outside a word */

/* count lines, words, characters. any sequence of characters without a blank, tab, or newline is a word */
main()
{
  int lc, wc, cc, c, state;

  state = OUT;
  lc = wc = cc = 0;

  while ((c = getchar()) != EOF) {
    // always increment char count
    ++cc;
    // increment line count if newline
    if (c == '\n')
      ++lc;
    // increment word count if we are outside of a word,
    // but then encounter a non space character
    if (c == ' ' || c == '\n' || c == '\t')
      state = OUT;
    else if (state == OUT) {
      state = IN;
      ++wc;
    }
  }

  printf("lines: %d, words: %d, characters: %d", lc, wc, cc);
}

/* 1-11 how would we test this program?
 * - no input
 * - whitespace chars that are not ' ', newlines, or tabs
 * - can we trick it into thinking its in a word when it isn't?
 * - tabular data, figures and numbers, etc.
 * - doesn't account for duplicate newlines - should they count?
 */

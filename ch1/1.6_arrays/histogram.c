#include <stdio.h>

#define IN              0    /* whether we're in a word */
#define OUT             1    /* whether we're outside of a word */
#define MAX_WORD_LENGTH 100  /* maximum word length tracked */

/* prints a histogram of word lengths in the input */
main() {
  int word_lengths[MAX_WORD_LENGTH + 1];
  int c, current_wl, state;

  for (int i = 0; i < (MAX_WORD_LENGTH + 1); ++i)
    word_lengths[i] = 0;

  state = OUT;
  current_wl = 0;

  while ((c = getchar()) != EOF)
    if (c == ' ' || c == '\n' || c == '\t') {
      state = OUT;
      if (current_wl < MAX_WORD_LENGTH + 1) {
        ++word_lengths[current_wl];
      } else {
        ++word_lengths[MAX_WORD_LENGTH];
      }
      current_wl = 0;
    } else if (state = OUT) {
      state = IN;
      ++current_wl;
    }

  // horizontal histogram
  for (int i = 1; i < (MAX_WORD_LENGTH + 1); ++i) {
    if (word_lengths[i] > 0) {
      printf("%3d: ", i);
      for (int j = 0; j < word_lengths[i]; ++j)
        printf("-");
      printf("\n");
    }
  }

  printf("\n");
  printf("\n");
  printf("\n");
  printf("\n");

  // vertical histogram
  int max_height = 0;
  for (int i = 1; i < (MAX_WORD_LENGTH + 1); ++i) {
    if (word_lengths[i] > max_height)
      max_height = word_lengths[i];
  }

  for (int i = max_height; i > 0; --i) {
    for (int j = 1; j < MAX_WORD_LENGTH; ++j) {
      if (word_lengths[j] >= i)
        printf("    |");
      else if (word_lengths[j] > 0)
        printf("     ");
    }
    printf("\n");
  }

  for (int i = 1; i < MAX_WORD_LENGTH; ++i)
    if (word_lengths[i] > 0)
      printf("=====");

  printf("\n");

  for (int i = 1; i < MAX_WORD_LENGTH; ++i)
    if (word_lengths[i] > 0)
      printf("%5d", i);
}

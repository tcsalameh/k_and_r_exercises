#include <stdio.h>
#include <limits.h>

#define MAX_HIST_SIZE 30   /* maximum height of the histogram bars */

main()
{
  int char_freqs[CHAR_MAX];
  int c;

  for (int i = 0; i < CHAR_MAX; ++i)
    char_freqs[i] = 0;

  while ((c = getchar()) != EOF) {
    ++char_freqs[c];
  }

  // get max so we can scale
  int max_freq = 0;
  for (int i = 1; i < CHAR_MAX; ++i)
    if (max_freq < char_freqs[i])
      max_freq = char_freqs[i];

  int scale_factor = max_freq / MAX_HIST_SIZE;

  // horizontal histogram
  for (int i = 1; i < CHAR_MAX; ++i) {
    if (char_freqs[i] > 0) {
      printf("%3c: ", i);
      for (int j = 0; j < char_freqs[i]; j += scale_factor)
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
  for (int i = 0; i < CHAR_MAX; ++i) {
    if (char_freqs[i] > max_height)
      max_height = char_freqs[i];
  }

  for (int i = max_height; i > 0; i -= scale_factor) {
    for (int j = 0; j < CHAR_MAX; ++j) {
      if (char_freqs[j] >= i)
        printf("  |");
      else if (char_freqs[j] > 0)
        printf("   ");
    }
    printf("\n");
  }

  for (int i = 0; i < CHAR_MAX; ++i)
    if (char_freqs[i] > 0)
      printf("===");

  printf("\n");

  for (int i = 0; i < CHAR_MAX; ++i)
    if (char_freqs[i] > 0)
      printf("%3c", i);
}

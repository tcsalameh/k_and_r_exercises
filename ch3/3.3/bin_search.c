/* Our binary search makes two tests
 * inside the loop, when one would suffice
 * (at the price of more tests outside). Write
 * a version with only one test inside the loop
 * and measure the difference in run-time */

// Result: modified search is pretty consistently faster
// by 1-5%.
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define TEST_SIZE       1000000    /* Size of test array */
#define TRIALS          20         /* Number of trials to run */
#define TESTS_PER_TRIAL 10000      /* Number of lookups per trial */

int bin_search_a(int x, int v[], int n);
int bin_search_b(int x, int v[], int n);

int main()
{

  struct timeval stop, start;
  int ary[TEST_SIZE];
  int search_number;
  int time_taken;
  int total_time_a = 0;
  int total_time_b = 0;

  for (int i=0; i<TEST_SIZE; i++)
    ary[i] = i;

  for (int t=0; t<TRIALS; t++) {
    gettimeofday(&start, NULL);
    for (int i=0; i<TESTS_PER_TRIAL; i++) {
      srand(start.tv_usec);
      search_number = rand() % 10000000;
      bin_search_a(search_number, ary, 1000000);
    }
    gettimeofday(&stop, NULL);
    total_time_a += stop.tv_usec - start.tv_usec;

    gettimeofday(&start, NULL);
    for (int i=0; i<TESTS_PER_TRIAL; i++) {
      srand(start.tv_usec);
      search_number = rand() % 10000000;
      bin_search_b(search_number, ary, 1000000);
    }
    gettimeofday(&stop, NULL);
    total_time_b += stop.tv_usec - start.tv_usec;
  }

  int avg_time_a = total_time_a / TRIALS;
  int avg_time_b = total_time_b / TRIALS;
  printf("Average time taken across %d trials by bin_search_a: %d\n", TRIALS, avg_time_a);
  printf("Average time taken across %d trials by bin_search_b: %d\n", TRIALS, avg_time_b);
  printf(
      "%s was faster by %d microseconds on average!\n",
      (total_time_a > total_time_b) ? "bin_search_b" : "bin_search_a",
      abs(avg_time_a - avg_time_b)
  );
}

int bin_search_a(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;
  while (low <= high) {
    mid = (low+high) / 2;
    if (x < v[mid])
      high = mid - 1;
    else if (x > v[mid])
      low = mid + 1;
    else
      return mid; /* found match */
  }
  return -1;  /* no match */
}

int bin_search_b(int x, int v[], int n)
{
  int low, high, mid;

  low = 0;
  high = n - 1;

  while (low <= high) {
    mid = (low+high) / 2;
    if (x <= v[mid])
      high = mid - 1;
    else
      low = mid + 1;
  }
  if (x == v[mid])
    return mid; /* found match */
  else
    return -1;  /* no match */
}


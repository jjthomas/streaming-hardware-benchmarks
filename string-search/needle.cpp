#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>


using namespace std;

int main(int argc, char **argv) {
  int HAYSTACK_SIZE = atoi(argv[1]);
  int NEEDLE_SIZE = atoi(argv[2]);
  char *haystack = new char[HAYSTACK_SIZE];
  char *needle = new char[NEEDLE_SIZE];
  for (int i = 0; i < HAYSTACK_SIZE; i++) {
    haystack[i] = (char)(rand());
  }
  for (int i = 0; i < NEEDLE_SIZE; i++) {
    needle[i] = (char)(rand());
  }

  int sum = 0;
  struct timeval start, end, diff;
  gettimeofday(&start, 0);
  for (int i = NEEDLE_SIZE; i <= HAYSTACK_SIZE; i++) {
    bool mismatch = false; 
    for (int j = i - NEEDLE_SIZE; j < i; j++) { 
      if (haystack[j] != needle[j - (i - NEEDLE_SIZE)]) {
        mismatch = true;
      }
    }
    if (!mismatch) {
      sum++;
    }
  }
  gettimeofday(&end, 0);
  timersub(&end, &start, &diff);
  printf("%d: %ld.%06ld\n", sum, (long)diff.tv_sec, (long)diff.tv_usec);

  return 0;
}

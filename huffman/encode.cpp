#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>


using namespace std;

int main(int argc, char **argv) {
  int NUM_BYTES = atoi(argv[1]);
  int DICT_SIZE = atoi(argv[2]);
  assert(DICT_SIZE <= 255);
  uint8_t *input = new uint8_t[NUM_BYTES];
  uint8_t *dict = new uint8_t[DICT_SIZE];
  int *dict_lens = new int[DICT_SIZE];
  uint64_t *output = new uint64_t[NUM_BYTES / 8];
  for (int i = 0; i < NUM_BYTES; i++) {
    input[i] = (uint8_t)(rand() % DICT_SIZE);
  }
  for (int i = 0; i < DICT_SIZE; i++) {
    dict[i] = i; 
    int len = 1;
    while ((i >> len) != 0) {
      len++;
    }
    dict_lens[i] = len;
  }

  int num_output_words = 0;
  uint64_t cur = 0;
  int cur_len = 0;
  struct timeval start, end, diff;
  gettimeofday(&start, 0);
  for (int i = 0; i < NUM_BYTES; i++) {
    uint64_t sym = dict[input[i]];
    int len = dict_lens[input[i]];
    cur = cur | ((sym & ((1L << (64 - cur_len)) - 1)) << cur_len);
    cur_len += len;
    if (cur_len >= 64) {
      output[num_output_words++] = cur;
      cur_len -= 64;
      cur = sym >> (len - cur_len);
    }
  }
  if (cur_len > 0) {
    output[num_output_words++] = cur;
  }
  gettimeofday(&end, 0);
  timersub(&end, &start, &diff);
  printf("%" PRIu64 ": %ld.%06ld\n", output[num_output_words - 1], (long)diff.tv_sec, (long)diff.tv_usec);

  return 0;
}

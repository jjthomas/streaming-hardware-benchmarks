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
  uint8_t *output = new uint8_t[NUM_BYTES * 8];
  for (int i = 0; i < NUM_BYTES; i++) {
    input[i] = (uint8_t)(rand() % 256);
  }
  for (int i = 0; i < DICT_SIZE; i++) {
    dict[i] = i;
  }

  int num_output_bytes = 0;
  int cur_num_ones = 0;
  struct timeval start, end, diff;
  gettimeofday(&start, 0);
  for (int i = 0; i < NUM_BYTES; i++) {
    for (int j = 0; j < 8; j++) {
      if ((input[i] >> j) & 1) {
        cur_num_ones++;
      } else {
        output[num_output_bytes++] = dict[cur_num_ones >= DICT_SIZE ? DICT_SIZE - 1 : cur_num_ones];
	cur_num_ones = 0;
      }
    }
  }
  gettimeofday(&end, 0);
  timersub(&end, &start, &diff);
  printf("%d: %ld.%06ld\n", (int)output[num_output_bytes - 1], (long)diff.tv_sec, (long)diff.tv_usec);

  return 0;
}

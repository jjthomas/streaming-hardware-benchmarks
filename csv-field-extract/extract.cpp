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
  int FIELD_SIZE = atoi(argv[1]);
  int NUM_FIELDS = atoi(argv[2]);
  int NUM_ROWS = atoi(argv[3]);
  int TARGET_FIELD = atoi(argv[4]);
  char *csv = new char[(FIELD_SIZE + 1) * NUM_FIELDS * NUM_ROWS];
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_FIELDS; j++) {
      for (int k = 0; k < FIELD_SIZE; k++) {
        csv[i * (FIELD_SIZE + 1) * NUM_FIELDS + (FIELD_SIZE + 1) * j + k] = (char)('0' + (rand() % 10));
      }
      csv[i * (FIELD_SIZE + 1) * NUM_FIELDS + (FIELD_SIZE + 1) * j + FIELD_SIZE] = (j == NUM_FIELDS - 1) ? '\n' : ',';
    }
  }

  int sum = 0;
  int field_num = 0;
  bool in_quote = false;
  char last_char = ' ';
  struct timeval start, end, diff;
  gettimeofday(&start, 0);
  for (int i = 0; i < (FIELD_SIZE + 1) * NUM_FIELDS * NUM_ROWS; i++) {
    if (csv[i] == '"') {
      if (!in_quote) { 
        in_quote = true;
      } else {
        in_quote = last_char == '\\';
      }
    } else if (csv[i] == ',') {
      if (!in_quote) {
        field_num++;
      }
    } else if (csv[i] == '\n') {
      if (!in_quote) {
        field_num = 0;
      }
    }
    if (field_num == TARGET_FIELD && !(csv[i] == ',' && !in_quote)) {
      sum++;
    }
    last_char = csv[i];
  }
  gettimeofday(&end, 0);
  timersub(&end, &start, &diff);
  printf("%d: %ld.%06ld (%d chars)\n", sum, (long)diff.tv_sec, (long)diff.tv_usec, (FIELD_SIZE + 1) * NUM_FIELDS * NUM_ROWS);

  return 0;
}

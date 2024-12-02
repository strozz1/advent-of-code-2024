#include <stdio.h>
#include <stdlib.h>

// Delete the element on the target index
int subarray(int *array, int size, int target) {
  int i, j = 0;
  for (i = 0; i < size; i++) {
    if (i != target) {
      array[j] = array[i];
      j++;
    }
  }
  return size - 1;
}
int check_greater(int *array, int pos, int size) {
  if (size > 1) {
    int diff = abs(array[pos] - array[pos - 1]);
    if (array[pos] > array[pos - 1] && (1 <= diff && diff <= 3)) {
      return check_greater(array, pos + 1, size - 1);
    } else {
      return pos;
    }
  }
  return -1;
}

int check_lesser(int *array, int pos, int size) {
  if (size > 1) {
    int diff = abs(array[pos - 1] - array[pos]);
    if (array[pos - 1] > array[pos] && (1 <= diff && diff <= 3)) {
      return check_lesser(array, pos + 1, size - 1);
    } else {
      return pos;
    }
  }
  return -1;
}
int check_if_valid(int *array, int size) {
  int val = 0;
  if (array[1] > array[0]) {
    val = check_greater(array, 1, size);
  } else if (array[1] < array[0]) {
    val = check_lesser(array, 1, size);
  }

  return val;
}

int main(void) {
  int i = 0;
  char *f_name = "input.txt";
  FILE *fd = fopen(f_name, "r");
  int safe = 0;
  char number[30];
  char c;
  int line[30];
  int size = 0;

  while (fscanf(fd, "%c", &c) > 0) {
    if (c == '\n') {
      number[i] = '\0';
      sscanf(number, "%d", &line[size]);

      size++;
      int val = check_if_valid(line, size);

      if (val != -1) {
        subarray(line, size, val);
        size = size - 1;
        val = check_if_valid(line, size);

      }

      if (val == -1) {
        safe++;
      } 
      size = 0;
      i = 0;
      continue;
    }
    if (c == ' ') {
      // parse word to int
      number[i] = '\0';
      sscanf(number, "%d", &line[size]);
      size++;
      i = 0;
    } else {
      // add char to word
      number[i] = c;
      i++;
    }
  }
  printf("Safe: %d\n", safe);
  return 0;
}

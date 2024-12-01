#include <stdio.h>
#include <stdlib.h>

int get_lines(FILE *file) {
  int count = 0;
  char ch;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      count++;
    }
  }
  fseek(file, 0, SEEK_SET);
  return count;
}

int get_similarities(int *left, int *right, int size) {
  int sum = 0, i, j, quant;
  for (i = 0; i < size; i++) {
    quant = 0;
    for (j = 0; right[j] <= left[i] || j < size; j++) {
      if (left[i] == right[j]) {
        quant++;
      }
    }
    sum += left[i] * quant;
  }
  return sum;
}
void add_ordered(int *list, int size, int num) {
  int i = 0;
  int tmp = num;
  int tmp2 = 0;
  for (i = 0; i < size; i++) {
    // if 0, then the value is empty
    if (list[i] == 0) {
      list[i] = tmp;
      return;
    }
    if (list[i] > tmp) {
      tmp2 = list[i];
      list[i] = tmp;
      tmp = tmp2;
    }
  }
}

int main(int argc, char *args[]) {
  char *file_name = "";
  FILE *file;
  int num;
  int it, i = 0;
  int *left;
  int *right;
  int lines = 0;
  int sum = 0;
  int sims;
  if (argc < 2) {
    printf("You must provide a file\n");
    return -1;
  }

  file_name = args[1];
  file = fopen(file_name, "r");

  printf("File: %s\n", file_name);
  lines = get_lines(file);
  left = (int *)malloc(lines * sizeof(int));
  right = (int *)malloc(lines * sizeof(int));

  while (fscanf(file, "%d", &num) == 1) {

    if (it % 2 == 0) {
      add_ordered(left, lines, num);
    } else {
      add_ordered(right, lines, num);
    }
    it++;
  }
  for (i = 0; i < lines; i++) {
    sum += abs(left[i] - right[i]);
  }
  printf("Sum: %d\n", sum);

  sims = get_similarities(left, right, lines);
  printf("Similarities: %d\n", sims);
  free(left);
  free(right);

  return 0;
}

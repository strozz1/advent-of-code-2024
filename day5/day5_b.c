#include "order.c"
#include <_string.h>
#include <stdio.h>
#include <string.h>
// the idea is have a hashmap sort of data structure that contains with elements
// has to be before de index so if 23 & 4 has to be before 43, it would be like
// [43]=[23,4]; meaning that if it encounters 43 before one of those elements,
// BAD! for this problem im not going to use a hasmap, just a simple list with
// structs!

void parse_file(FILE *fd, Restrictions *r) {
  int n1, n2;
  while (fscanf(fd, "%d|%d", &n1, &n2) == 2) {
    add_restriction(r, n2, n1);
  }
  fseek(fd, -2, SEEK_CUR);
}
int check_order(Restrictions *r, int *line, int size) {
  int i, j;
  Restriction *rest;
  int tmp, is_incorrect = 0;

  for (i = 0; i < size; i++) {
    rest = get_restriction(r, line[i]);
    if (rest == NULL) {
      continue;
    }

    for (j = i+1; j < size; j++) {
      if (is_before(rest, line[j])) {
        tmp = line[j];
        line[j] = line[i];
        line[i] = tmp;
        i=0;

        is_incorrect = 1;
      }
    }
  }
  return is_incorrect == 1 ? line[size / 2] : 0;
}
int parse_line(char *line, Restrictions *r) {
  int i, n = 0;
  int *values = (int *)malloc(0);
  line = strtok(line, ",");

  while (line) {
    if (sscanf(line, "%d", &i) == 1) {
      n++;
      values = realloc(values, sizeof(int) * n);
      values[n - 1] = i;
    }
    line = strtok(NULL, ",");
  }
  return check_order(r, values, n);
}
int check_lines(FILE *fd, Restrictions *r) {
  char line[100];
  int count = 0;
  while (fscanf(fd, "%s", line) > 0) {
    count += parse_line(line, r);
  }
  return count;
}
int main(int argc, char **argv) {
  FILE *fd;
  int count = 0;
  Restrictions *r = init_restrictions();
  if (argc < 2) {
    printf("FILE?\n");
    return 1;
  }
  fd = fopen(argv[1], "r");
  if (fd == NULL) {
    printf("Error opening file!\n");
    return 1;
  }

  parse_file(fd, r);
  count = check_lines(fd, r);
  printf("Count: %d\n", count);
  return 0;
}

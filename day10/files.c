#include <stdio.h>
int get_lines(FILE *fd) {
  char s[1024];
  int i = 0;
  while (fscanf(fd, "%s\n", s) > 0) {
    i++;
  }
  fseek(fd, 0, SEEK_SET);
  return i;
}

int get_length(FILE *fd) {
  char c;
  int i = 0;
  while (fscanf(fd, "%c", &c) > 0) {
    if (c == '\n') {
      break;
    }
    i++;
  }
  fseek(fd, 0, SEEK_SET);
  return i;
}



void print_map(int *map, int h, int w) {
  int i;
  for (i = 0; i < h * w; i++) {
    if (i % w == 0) {
      printf("\n");
    }
    printf("%d", map[i]);
  }
  printf("\n");
}

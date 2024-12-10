#include "files.c"
#include <stdio.h>
#include <stdlib.h>

int visited(int *list, int size, int val) {
  int i;
  for (i = 0; i < size; i++) {
    if (list[i] == val)
      return 1;
  }
  return 0;
}
int visited_nodes[256];
int size = 0;
int backtracking(int *map, int height, int width, int pos) {
  int count = 0;
  int w, h;
  if (map[pos] == 9) {
    if (visited(visited_nodes, size, pos)) {
        //for part 2, remove this if statement
      return 0;
    }
    visited_nodes[size] = pos;
    size++;
    printf("YEah :%d\n",pos);
    return 1;
  }
  w = pos % width;
  h = pos / width;

  // right
  if (w < width-1 && map[pos] + 1 == map[pos + 1]) {
    count += backtracking(map, height, width, pos + 1);
  }
  // left
  if (w > 0 && map[pos] + 1 == map[pos - 1]) {
    count += backtracking(map, height, width, pos - 1);
  }
  if (h > 0 && map[pos] + 1 == map[pos - width]) {
    count += backtracking(map, height, width, pos - width);
  }
  if (h < height-1 && map[pos] + 1 == map[pos + width]) {
    count += backtracking(map, height, width, pos + width);
  }
  return count;
}
int search(int *map, int height, int width) {
  int i, count = 0;
  for (i = 0; i <= height * width; i++) {
    if (map[i] == 0) {
      size = 0;
      count+= backtracking(map, height, width, i);
    }
  }
  return count;
}
int *read_map(FILE *fd, int height, int width) {
  int line = 0, curr = 0;
  int c;
  int *map = (int *)malloc(sizeof(int) * height * width);
  if (map == NULL) {
    printf("Error malloc map\n");
    return NULL;
  }

  while (fscanf(fd, "%1d", &c) > 0) {
    if (c == '\n') {
      line++;
      curr = 0;
      continue;
    }
    map[line * width + curr] = c;
    curr++;
  }
  return map;
}
void parse_file(FILE *fd) {
  int height = get_lines(fd);
  int width = get_length(fd);
  int *map = read_map(fd, height, width);
  int count;
  printf("%d %d\n", width, height);
  print_map(map, height, width);
  count = search(map, height, width);
  printf("Count: %d\n", count);
}

int main(int argc, char **args) {
  FILE *fd;
  if (argc < 2) {
    printf("FILE?\n");
    return 1;
  }
  fd = fopen(args[1], "r");
  if (fd == NULL) {
    printf("Error opening file\n");
    return 1;
  }
  parse_file(fd);
}

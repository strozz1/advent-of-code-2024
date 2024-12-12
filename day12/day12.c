#include "files.c"
#include <stdio.h>
#include <stdlib.h>
char *visited;
int bsize = 0;

int check_visited(char *visited, int size, char val) {
  int i;
  for (i = 0; i < size; i++) {
    if (visited[i] == val)
      return 1;
  }
  return 0;
}
void backtracking(char *map, int w, int h, int pos, int *area, int *perim) {
  if (check_visited(visited, bsize, pos)) {
    return;
  }
  (*area)++;

  visited[bsize] = pos;
  bsize++;
  int curr_w = pos % w, curr_h = pos / w;
  char current = map[pos];
  // left
  if (curr_w <= 0 || (current != map[pos - 1])) {
    (*perim)++;
  } else {
    backtracking(map, w, h, pos - 1, area, perim);
  }
  if (curr_h <= 0 || (current != map[pos - w])) {

    (*perim)++;
  } else {
    backtracking(map, w, h, pos - w, area, perim);
  }
  if (curr_w >= w - 1 || (current != map[pos + 1])) {

    (*perim)++;
  } else {
    backtracking(map, w, h, pos + 1, area, perim);
  }
  if (curr_h >= h - 1 || (current != map[pos + w])) {
    (*perim)++;
  } else {
    backtracking(map, w, h, pos + w, area, perim);
  }
}

void resolve(char *map, int width, int height) {
  int i;
  int sum = 0;
  int area, perim;
  visited=malloc(sizeof(char)*width*height);

  for (i = 0; i < width * height; i++) {
    area = 0;
    perim = 0;

    backtracking(map, width, height, i, &area, &perim);
    sum += area * perim;
  }
    printf("Total: %d\n", sum);

}
int main(int argc, char **args) {
  char *map;
  FILE *fd;
  int width, height;
  if (argc < 2) {
    printf("FILE?\n");
    return 1;
  }
  fd = fopen(args[1], "r");
  if (fd == NULL) {
    printf("Cant open file\n");
    return 1;
  }
  width = get_length(fd);
  height = get_lines(fd);
  printf("(%d,%d)\n",width,height);
  map = read_map(fd, width, height);
  print_map(map, width, height);
  resolve(map, width, height);
  fclose(fd);
  free(map);
}

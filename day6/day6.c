#include "files.c"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int w;
  int h;
} Pos;

int check_obs(char *map, int height, int width, Pos pos) {
  if (pos.w < width && pos.h < height && pos.w >= 0 && pos.h >= 0) {
    return map[pos.h * width + pos.w] == '#' ? 0 : 1;
  }
  return 1;
}
void get_pos(char *map, int height, int width, Pos *pos) {
  int i;
  for (i = 0; i < height * width; i++) {
    if (map[i] == '>' || map[i] == '<' || map[i] == '^' || map[i] == 'v') {
      pos->w = i % width;
      pos->h = i / width;
      break;
    }
  }
}
int path(char *map, int height, int width) {
  int count = 0;
  Pos pos, next;
  int ok = 1;
  get_pos(map, height, width, &pos);

  while (pos.w < width && pos.h < height && pos.w >= 0 &&
         pos.h >= 0) { // while inbound
    switch (map[pos.h * width + pos.w]) {
    case '^':
      next.w = pos.w;
      next.h = pos.h - 1;
      ok = check_obs(map, height, width, next);
      if (ok) {
        if (map[next.h * width + next.w] != 'X') {
          count++;
        }
        map[pos.h * width + pos.w] = 'X';
        map[next.h * width + next.w] = '^';
        pos.h = next.h;
      } else {
        map[pos.h * width + pos.w] = '>';
      }
      break;
    case '>':
      next.w = pos.w + 1;
      next.h = pos.h;
      ok = check_obs(map, height, width, next);
      if (ok) {
        if (map[next.h * width + next.w] != 'X') {
          count++;
        }
        map[pos.h * width + pos.w] = 'X';
        map[next.h * width + next.w] = '>';
        pos.w = next.w;
      } else {
        map[pos.h * width + pos.w] = 'v';
      }
      break;
    case 'v':
      next.w = pos.w;
      next.h = pos.h + 1;
      ok = check_obs(map, height, width, next);
      if (ok) {
        if (map[next.h * width + next.w] != 'X') {
          count++;
        }
        map[pos.h * width + pos.w] = 'X';
        map[next.h * width + next.w] = 'v';
        pos.h = next.h;
      } else {
        map[pos.h * width + pos.w] = '<';
      }
      break;
    case '<':
      next.w = pos.w - 1;
      next.h = pos.h;
      ok = check_obs(map, height, width, next);
      if (ok) {
        if (map[next.h * width + next.w] != 'X') {
          count++;
        }
        map[pos.h * width + pos.w] = 'X';
        map[next.h * width + next.w] = '<';
        pos.w = next.w;
      } else {
        map[pos.h * width + pos.w] = '^';
      }
      break;
    }
    //print_map(map, height, width);
  }
  return count;
}

char *read_map(FILE *fd, int height, int width) {
  int line = 0, curr = 0;
  char c;
  char *map = (char *)malloc(sizeof(char) * height * width);
  if (map == NULL) {
    printf("Error malloc map\n");
    return NULL;
  }

  while (fscanf(fd, "%c", &c) > 0) {
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
  char *map = read_map(fd, height, width);
  int count;
  printf("%d %d\n", width, height);
  print_map(map, height, width);
  count = path(map, height, width);
  printf("Count: %d\n", count);
}

int main(int argc, char **argv) {
  FILE *fd;
  if (argc < 2) {
    printf("Must pass file\n");
    return 1;
  }
  fd = fopen(argv[1], "r");
  if (fd == NULL) {
    printf("Cant open file\n");
    return 1;
  }
  parse_file(fd);
}

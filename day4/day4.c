

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print(char **contents, int len) {
  int i;
  for (i = 0; i < len; i++) {
    printf("%s\n", contents[i]);
  }
}
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
int up(char **contents, int w, int h) {
  int ii = 0;
  char *expected = "XMAS";
  for (ii = 0; ii < 4; ii++) {
    if (expected[ii] != contents[h-ii][w]) {
      return 0;
    }
  }
  return 1;
}
int down(char **contents, int w, int h) {
  int ii = 0;
  char *expected = "XMAS";
  for (ii = 0; ii < 4; ii++) {
    if (expected[ii] != contents[h+ii][w]) {
      return 0;
    }
  }
  return 1;
}
int left(char **contents, int w, int h) {
  int ii = 0;
  char *expected = "XMAS";
  for (ii = 0; ii < 4; ii++) {
    if (expected[ii] != contents[h][w-ii]) {
      return 0;
    }
  }
  return 1;
}
int right(char **contents, int w, int h) {
  int ii = 0;
  char *expected = "XMAS";
  for (ii = 0; ii < 4; ii++) {
    if (expected[ii] != contents[h][w+ii]) {
      return 0;
    }
  }
  return 1;
}
int right_to_left(char **contents, int w, int h) {
  int ii = 0;
  char *expected = "XMAS";
  for (ii = 0; ii < 4; ii++) {
    if (expected[ii] != contents[h-ii][w-ii]) {
      return 0;
    }
  }
  return 1;
}
int left_to_right(char **contents, int w, int h) {
  int ii = 0;
  char *expected = "XMAS";
  for (ii = 0; ii < 4; ii++) {
    if (expected[ii] != contents[h+ii][w-ii]) {
      return 0;
    }
  }
  return 1;
}
int downright(char **contents, int w, int h) {
  int ii = 0;
  char *expected = "XMAS";
  for (ii = 0; ii < 4; ii++) {
      printf("%c:%c (%d,%d)\n",expected[ii],contents[h+ii][w+ii],h+ii,w+ii);
    if (expected[ii] != contents[h+ii][w+ii]) {
      return 0;
    }
  }
  return 1;
}
int upright(char **contents, int w, int h) {
  int ii = 0;
  char *expected = "XMAS";
  for (ii = 0; ii < 4; ii++) {
    if (expected[ii] != contents[h-ii][w+ii]) {
      return 0;
    }
  }
  return 1;
}
int is_word(char **contents, int len, int w, int h) {
  int len2 = strlen(contents[0]);
  int count = 0;
  if (h >= 3) {
    count += up(contents, w, h);
  }
  if (h <= len - 4) {
    count += down(contents, w, h);
  }
  if (w >= 3) {
    count += left(contents, w, h);
  }
  if (w <= len2 - 4) {
    count += right(contents, w, h);
  }
  if( h>=3 && w>=3){
    count += right_to_left(contents, w, h);
  }
  if( h <= len - 4 && w>=3){
    count += left_to_right(contents, w, h);
  }
  if( h >= 3 && w <= len2 - 4){
    count += upright(contents, w, h);
  }
  if( h <= len - 4 && w <= len2 - 4){
    count += downright(contents, w, h);
  }
  
  return count;
}
int search(char **contents, int len) {
  int h, w, sum = 0;
  int len2 = strlen(contents[0]);
  for (h = 0; h < len; h++) {
    for (w = 0; w < len2; w++) {
      if (contents[h][w] == 'X') {
        sum += is_word(contents, len, w, h);
      }
    }
  }
  return sum;
}
int main(int argc, char **argv) {
  FILE *file;
  int len;
  char *line;
  char c = 1;
  int i = 0, lines = 0, count = 0;
  char **contents;

  if (argc < 2) {
    printf("FILE????\n");
    return 1;
  }
  file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  len = get_length(file);
  lines = get_lines(file);
  contents = (char **)malloc(sizeof(char *) * lines);

  while (1) {
    line = (char *)malloc(sizeof(char) * len);
    c = fscanf(file, "%s", line);
    if (c < 0)
      break;
    contents[i] = line;
    i++;
  }
  print(contents, lines);

  count = search(contents, len);
  printf("count: %d\n", count);
  fclose(file);
}

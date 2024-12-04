

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
int right_to_left(char **contents, int w, int h) {
  int ii = 0;
  char *expected = "MAS";
  int count = 2;
  for (ii = -1; ii < 2; ii++) {
      printf("(%d,%d)->%c,%c\n",h+ii,w-ii,expected[ii+1],contents[h + ii][w - ii] );

    if (expected[ii + 1] != contents[h + ii][w - ii]) {
        printf("NO !\n");
      count--;
      break;
    }
  }
  // check other direction
  for (ii = -1; ii < 2; ii++) {
      printf("2: (%d,%d)->%c,%c\n",h-ii,w+ii,expected[ii+1],contents[h - ii][w + ii] );

    if (expected[ii + 1] != contents[h - ii][w + ii]) {
        printf("NO 2!\n");

      count--;
      break;
    }
  }

  return count;
}
int left_to_right(char **contents, int w, int h) {
  int ii = 0;
  char *expected = "MAS";
  int count = 2;
  for (ii = -1; ii < 2; ii++) {
      printf("(%d,%d)->%c,%c\n",h+ii,w+ii,expected[ii+1],contents[h + ii][w + ii] );
    if (expected[ii + 1] != contents[h + ii][w + ii]) {
        printf("done!\n");
      count--;
      break;
    }
  }
  // check other direction
  for (ii = -1; ii < 2; ii++) {
      printf("2: (%d,%d)->%c,%c\n",h-ii,w-ii,expected[ii+1],contents[h - ii][w - ii] );

    if (expected[ii + 1] != contents[h - ii][w - ii]) {
        printf("done 2!\n");
      count--;
      break;
    }
  }

  return count;
}
int is_word(char **contents, int len, int w, int h) {
  int len2 = strlen(contents[0]);
  int count = 0;

  if (h >= 1 && w >= 1 && h < len - 1 &&
      w < len2 - 1) { // left to right diagonal
    count += left_to_right(contents, w, h);
  }
  if (h >= 1 && w < len2 - 1 && h < len - 1 && w >= 1) {
    count += right_to_left(contents, w, h);
  }
  return count==2?1:0;
}
int search(char **contents, int len) {
  int h, w, sum = 0;
  int len2 = strlen(contents[0]);
  for (h = 1; h < len-1; h++) {
    for (w = 1; w < len2-1; w++) {
      if (contents[h][w] == 'A') {
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
  printf("Count: %d\n", count);
  fclose(file);
}

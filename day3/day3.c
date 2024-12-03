#include <ctype.h>
#include <stdio.h>
#include <string.h>

int get_word(FILE *fd) {
  int i = 1;
  char *expected = "mul(";
  char c;
  char num[4];
  int num1, num2;

  // check if mul(l
  while (fscanf(fd, "%c", &c) > 0 && i < 3) {

    if (c != expected[i]) {
      return 0;
    }
    i++;
  }
  // If here, we succesfully passed mul( zone. now the numbers
  // The numbers can be max 3 digits
  i = 0;
  while (fscanf(fd, "%c", &c) > 0 && i < 3) {
    if (!isdigit(c)) {
      if (i == 0) {
        if (c == 'm') {
          return get_word(fd);
        }

        // if i=0 means that no digit
        return 0;
      }
      break;
    }
    num[i] = c;
    i++;
  }
  num[i] = '\0';
  // parse num
  sscanf(num, "%d", &num1);

  if (c != ',') {
    if (c == 'm') {
      return get_word(fd);
    }

    return 0;
  }

  // scan second number
  i = 0;
  while (fscanf(fd, "%c", &c) > 0 && i < 3) {
    if (!isdigit(c)) {
      if (i == 0) {
        if (c == 'm') {
          return get_word(fd);
        }

        // if i=0 means that no digit
        return 0;
      }
      break;
    }
    num[i] = c;
    i++;
  }
  num[i] = '\0';
  // parse num
  sscanf(num, "%d", &num2);

  if (c != ')') {
    if (c == 'm') {
      return get_word(fd);
    }
    return 0;
  }

  printf("mul(%d,%d)\n", num1, num2);

  return num1 * num2;
}

void tokenize(FILE *fd) {
  char c;
  int sum = 0;

  while (fscanf(fd, "%c", &c) > 0) {
    if (c == 'm') {
      sum += get_word(fd);
    }
  }
  printf("%d\n", sum);
}
int main(int argc, char **args) {
  char *file = args[1];
  FILE *fd = fopen(file, "r");
  if (fd == NULL) {
    printf("Error opening file\n");
    return 1;
  }

  tokenize(fd);
}

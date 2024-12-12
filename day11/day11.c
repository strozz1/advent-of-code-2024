#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *space(char *word, long *size) {
  word[*size] = ' ';
  *size += 1;
  word[*size] = '\0';
  return word;
}
char *trim_zeros(char *word) {
  long len = strlen(word);
  long i;
  for (i = 0; i < len; i++) {
    if (word[i] != '0') {
      return word + i;
    }
  }

  return word + i - 1;
}
char *norule(char *word, long *size, long num) {
  char parsed[50];
  num = num * 2024;
  long len = sprintf(parsed, "%ld", num);
  strcpy(&word[*size], parsed);

  (*size) += len;
  return word;
}
char *blink(char *line, long *max) {
  long len, size = 0;
  char *word;
  char parsed[50];
  
  char *newword = malloc(sizeof(char) * (*max));
  long num;
  word = strtok(line, " ");
  do {
    len = strlen(word);
    if (size != 0) { // add space before alloc
      newword = space(newword, &size);
    }
    if (len == 1) { // 1 digit
      sscanf(word, "%1ld", &num);
      if (num == 0) {
        num = 1;
        sprintf(parsed, "%ld", num);
        strcpy(&newword[size], parsed);
        size += len;
      } else {
        newword = norule(newword, &size, num);
      }
    } else if (len % 2 == 0) { // even
      if (len + size > *max) {
        *max *= 2;
        newword = realloc(newword, sizeof(char) * *max);
      }
      len = len / 2;
      strncpy(&newword[size], word, len);

      size += len;
      newword = space(newword, &size);
      word = trim_zeros(word + len);
      len = strlen(word);
      strcpy(&newword[size], word);
      size += len;
    } else {
      sscanf(word, "%ld", &num);
      if (len + size > *max) {
        *max *= 2;
        newword = realloc(newword, sizeof(char) * *max);
      }

      newword = norule(newword, &size, num);
    }

  } while ((word = strtok(NULL, " \n")) != NULL);

  return newword;
}
int main(int argc, char **args) {
  long j, n = 1;
  long max = 2^1024;
  FILE *fd;
  size_t m = 50;
  int i, iterations = 75;
  char *line = malloc(1024);
  if (argc < 2) {
    printf("FILE?\n");
    return 1;
  }
  fd = fopen(args[1], "r");
  if (fd == NULL) {
    printf("FIle not found\n");
    return 1;
  }
  getline(&line, &m, fd);

  for (i = 0; i < iterations; i++) {
    printf("I: %i, size:%ld with max %ld\n", i,strlen(line),max);
    line = blink(line, &max);
    // printf("%d: %s\n", i, line);
    n = 1;
    for (j = 0; j < strlen(line); j++) {
      if (line[j] == ' ')
        n++;
    }
  }
  printf("n:%ld\n", n);

  fclose(fd);
  return 0;
}

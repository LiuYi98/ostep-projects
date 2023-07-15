#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_fd(FILE *fp, char *buffer, size_t length, char *pattern) {

  ssize_t res = 0;
  char *substring;
  if (fp == NULL) {
    printf("wgrep: cannot open file\n");
    exit(EXIT_FAILURE);
  }
  while (true) {
    res = getline(&buffer, &length, fp);
    if (res == -1) {
      if (errno != 0) {
        perror("getline error");
      }
      break;
    }
    substring = strstr(buffer, pattern);
    if (substring == NULL) {
      continue;
    }
    printf("%s", buffer);
  }
}

int main(int argc, char *argv[]) {

  if (argc == 1) {
    printf("wgrep: searchterm [file ...]\n");
    exit(EXIT_FAILURE);
  }

  char *pattern = argv[1];
  char *buffer = NULL;
  size_t length = 0;
  if (argc == 2) {
    process_fd(stdin, buffer, length, pattern);
  }

  for (int i = 2; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    process_fd(fp, buffer, length, pattern);
  }
  return EXIT_SUCCESS;
}

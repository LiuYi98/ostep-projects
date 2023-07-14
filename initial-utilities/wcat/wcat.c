#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 10000

int main(int argc, char *argv[]) {

  if (argc == 1) {
    exit(EXIT_SUCCESS);
  }
  char *buffer;
  size_t size;
  ssize_t res = 0;
  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");
    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      exit(1);
    }
    while (true) {
      res = getline(&buffer, &size, fp);
      if (res == -1) {
        break;
      }
      printf("%s", buffer);
    }
    // printf("errno = %d\n", errno);
  }
  return EXIT_SUCCESS;
}

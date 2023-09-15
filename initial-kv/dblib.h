
#ifndef DBLIB_H

#define DBLIB_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int key;
  size_t length;
  char *value;
  bool deleted;
} Record;

typedef struct {
  size_t length;
  Record* records;
} Database;

#endif

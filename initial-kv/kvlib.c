#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int key;
  size_t length;
  char *value;
  bool deleted;
} Record;

typedef struct {
  size_t length;
  Record *values;
} Database;

typedef struct {
  char c;
  int key;
  char *value;

} Command;

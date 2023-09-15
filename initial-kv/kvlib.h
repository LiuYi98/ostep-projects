#include <stdbool.h>
#include <stdlib.h>

#ifndef KVLIB_H

#define KVLIB_H

typedef char *String;


typedef struct {
  char c;
  int key;
  char *value;

} Command;

#endif

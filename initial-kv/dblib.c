#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dblib.h"

const char *FILE_PATH = "db.db";

void write_record(Record *one_record, FILE *fp) {
  if (fp == NULL) {
    return;
  }
  fwrite(&one_record->key, sizeof(one_record->key), 1, fp);
  fwrite(&one_record->length, sizeof(one_record->length), 1, fp);
  fwrite(one_record->value, sizeof(char), strlen(one_record->value) + 1, fp);
  fwrite(&one_record->deleted, sizeof(one_record->deleted), 1, fp);
}

void read_record(Record *one, FILE *fp) {
  if (fp == NULL) {
    return;
  }
  fread(&one->key, sizeof(one->key), 1, fp);
  fread(&one->length, sizeof(one->length), 1, fp);
  one->value = malloc((one->length + 1) * sizeof(char));
  if (one->value == NULL) {
    return;
  }
  fread(one->value, sizeof(char), one->length + 1, fp);
  fread(&one->deleted, sizeof(one->deleted), 1, fp);
}

Database *read_database() {
  FILE *fp = fopen(FILE_PATH, "r");
  if (fp == NULL) {
    perror("open database file failed");
    exit(EXIT_FAILURE);
  }
  Database *dbp = malloc(sizeof(Database));
  if (dbp == NULL) {
    perror("memory allocate failed for database");
    exit(EXIT_FAILURE);
  }
  fread(&dbp->length, sizeof(dbp->length), 1, fp);

  dbp->records = malloc(dbp->length * sizeof(Record));
  if (dbp->records == NULL) {
    perror("memory allocate failed for dbp.records");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < dbp->length; i++) {
    read_record(dbp->records + i, fp);
  }
  fclose(fp);
  return dbp;
}

void write_database(Database *dbptr) {
  FILE *fp = fopen(FILE_PATH, "w");
  if (fp == NULL) {
    return;
  }
  fwrite(&dbptr->length, sizeof(dbptr->length), 1, fp);
  for (int i = 0; i < dbptr->length; i++) {
    write_record(dbptr->records + i, fp);
  }
  fclose(fp);
}

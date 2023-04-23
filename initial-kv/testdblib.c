#include "dblib.c"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_record(Recordptr rptr) {
    if (rptr == NULL) {
        printf("Record[NULL]");
    }

    printf("Record[deteted=%s,", rptr->deleted ? "true" : "false");
    printf("key=%d,", rptr->key);
    printf("length=%zu,", rptr->length);
    printf("value=%s]\n", rptr->value);
}


int main() {

    Database database;
    database.length = 2;
    Recordptr recordptr = malloc(database.length * sizeof(Record));
    if (recordptr == NULL) {
        return -1;
    }
    database.records = recordptr;
    recordptr->deleted=false;
    recordptr->key = 1;
    char *s1 = "first test";
    recordptr->value = malloc(sizeof(char) * (strlen(s1) + 1));
    strcpy(recordptr->value, s1);
    recordptr->length = strlen(recordptr->value);
    print_record(recordptr);

    recordptr++;

    recordptr->deleted=false;
    recordptr->key = 2;
    recordptr->value = "second test";
    char *s2 = "second test";
    recordptr->value = malloc(sizeof(char) * (strlen(s2) + 1));
    strcpy(recordptr->value, s2);
    recordptr->length = strlen(recordptr->value);
    print_record(recordptr);
    write_database(&database);

    Database ndb;
    read_database(&ndb);
    print_record(ndb.records);
    print_record(ndb.records + 1);
}
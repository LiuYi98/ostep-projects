#include "kvlib.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


const char *FILE_PATH = "database.txt";



void
write_record(Record *one_record, FILE *fp) {
    if (fp == NULL) {
        return;
    }
    fwrite(&one_record->key, sizeof(one_record->key), 1, fp);
    fwrite(&one_record->length, sizeof(one_record->length), 1, fp);
    fwrite(one_record->value, sizeof(char), strlen(one_record->value) + 1, fp);
    fwrite(&one_record->deleted, sizeof(one_record->deleted), 1, fp);
}

void
read_record(Record *one, FILE *fp) {
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


int 
read_database(Database *this_database) {
    FILE *fp = fopen(FILE_PATH, "r");
    if (fp == NULL) {
        return -1;
    }
    fread(&this_database->length, sizeof(this_database->length), 1, fp);
    this_database->records = malloc(this_database->length * sizeof(Record));
    if (this_database->records == NULL) {
        return -1;
    }
    for (int i = 0; i < this_database->length; i++) {
        read_record(this_database->records + i, fp);
    }
    fclose(fp);
    return 0;
}

void 
write_database(Database *this_database) {
    FILE *fp = fopen(FILE_PATH, "w");
    if (fp == NULL) {
        return;
    }
    fwrite(&this_database->length, sizeof(this_database->length), 1, fp);
    for (int i = 0; i < this_database->length; i++) {
        write_record(this_database->records + i, fp);
    }
    fclose(fp);
}



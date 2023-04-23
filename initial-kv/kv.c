#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvlib.h"
#define FILE_PATH "database.txt"

void read_record(Recordptr one_record, FILE *fp);
void write_record(Recordptr recordptr, FILE *fp);
void process_put(Databaseptr this_database, Command *command);
Recordptr new_record_from_command(Command *command);

Command 
parse_command(char const *argv) {
    char *command_string = strdup(argv);
    char *comma = ",";
    Command command;
    
    char c = *strsep(&command_string, comma);
    if (c != 'p' && c != 'g' && c != 'a' && c != 'c' && c != 'd') {
        printf("bad command\n");
        return command;
    }
    command.c = c;

    char *key = strsep(&command_string, comma);
    if (key == NULL) {
        return command;
    }
    int k = atoi(key);
    command.key = k;

    char *value = strsep(&command_string, comma);
    if (value == NULL) {
        return command;
    }
    command.value = value;
    return command;
}

void
process_one_command(Database *this_database, char const *argv) {
    Command command = parse_command(argv);
    switch (command.c) {
    case 'g' :
        /* code */
        break;
    case 'p' :
        process_put(this_database, &command);
        break;
    case 'd' :
        break;
    case 'c' :
        break;
    case 'a' :
        break; 
    
    default:
        printf("error format: %s, skip this Command", argv);
        break;
    }
}

void 
process_get(Database *this_database, Command *command) {
    int max = this_database->length;
    for (int i = 0; i < max; i++) {
        Recordptr recordptr = this_database->records;
        if (recordptr->deleted == false && command->key == recordptr->key) {
            printf("value for %d is: %s", command->key, recordptr->value);
            break;
        }
    }
    printf("no record found for %d", command->key);
} 


void 
process_put(Database *this_database, Command *command) {
    int max = this_database->length;
    for (int i = 0; i < max; i++) {
        Recordptr recordptr = this_database->records;
        if (command->key == recordptr->key) {
            recordptr->deleted = true;
            break;
        }
    }
    Recordptr new_records = (Recordptr) realloc(this_database->records, this_database->length + 1);
    if (new_records == NULL) {
        return;
    }
    this_database->records = new_records;
    Recordptr new_record = new_record_from_command(command);
    if (new_record == NULL) {
        return;
    }
    *(new_records + max) = *new_record;
    return;
}




Recordptr 
new_record_from_command(Command *command) {
    Recordptr recordptr = malloc(sizeof(Record));
    if (recordptr == NULL) {
        return recordptr;
    }
    recordptr->deleted = false;
    recordptr->key = command->key;
    recordptr->length = strlen(command->value);
    String string = malloc(sizeof(char) * (recordptr->length + 1));
    if (string == NULL) {
        free(recordptr);
        return NULL;
    }
    recordptr->value = string;
    return recordptr;
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
}


void
write_record(Record *one_record, FILE *fp) {
    if (fp == NULL) {
        return;
    }
    fwrite(&one_record->key, sizeof(one_record->key), 1, fp);
    fwrite(&one_record->length, sizeof(one_record->length), 1, fp);
    fwrite(one_record->value, sizeof(char), strlen(one_record->value) + 1, fp);
    fwrite(&one_record->deleted, sizeof(one_record->deleted), 1, fp);
    fclose(fp);
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
    fclose(fp);
}

int 
main(int argc, char const *argv[])
{

    // Record *one_record = malloc(sizeof(Record));
    // if (one_record == NULL) {
    //     return 0;
    // }
    // one_record->deleted = false;
    // one_record->key = 1;
    // one_record->value = "test string";
    // one_record->length = strlen(one_record->value);

    // write_record(one_record);

    // Record *readed_record = malloc(sizeof(Record));
    // read_record(readed_record);
    // printf("%d\n", readed_record->key);
    // printf("%ld\n", readed_record->length);
    // printf("%d\n", readed_record->deleted);
    // printf("%s\n", readed_record->value);
    Database *this_database = malloc(sizeof(Database));
    if (this_database == NULL) {
        return -1;
    }
    read_database(this_database);
    if (this_database == NULL) {
        return -1;
    } 
    printf("argc = %d\n", argc);
    for(int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
        Command command = parse_command(argv[i]);
        // printf("%c\n", command.c);
        // printf("%d\n", command.key);
        // printf("%s\n", command.value);
        process_one_command(this_database, argv[i]);
    }
    
    return 0;
}

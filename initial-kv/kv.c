#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kvlib.c"
#define FILE_PATH "database.txt"

void read_record(Record *one_record, FILE *fp);
void write_record(const Record *one_record, FILE *fp);


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





void process_put(Database *this_database, Command *command) {
    int key;
    char *value;
    
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

void process_get(Database *this_database, Command *command) {
    this_database->values
}

int 
read_database(Database *this_database) {
    FILE *fp = fopen(FILE_PATH, "r");
    if (fp == NULL) {
        return -1;
    }
    fread(&this_database->length, sizeof(this_database->length), 1, fp);
    this_database->values = malloc(this_database->length * sizeof(Record));
    if (this_database->values == NULL) {
        return -1;
    }
    for (int i = 0; i < this_database->length; i++) {
        read_record(this_database->values + i, fp);
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
        write_record(this_database->values + i, fp);
    }
}


void
write_record(const Record *one_record, FILE *fp) {
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

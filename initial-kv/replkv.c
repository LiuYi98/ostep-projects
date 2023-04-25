
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dblib.c"
#include "cmd.c"

#define FILE_PATH "database.txt"

void 
process_get(Databaseptr dbptr, Command *command) {
    Recordptr recordptr = dbptr->records;
    for (int i = 0; i < dbptr->length; i++) {
        if (recordptr->deleted == false && command->key == recordptr->key) {
            printf("value for %d is: %s", command->key, recordptr->value);
            return;
        }
        recordptr++;
    }
    printf("no record found for %d", command->key);
} 


void 
process_put(Databaseptr dbptr, Command *command) {
    Recordptr recordptr = dbptr->records;
    for (int i = 0; i < dbptr->length; i++) {
        if (command->key == recordptr->key) {
            recordptr->deleted = true;
            break;
        }
        recordptr++;
    }
    Recordptr new_records = realloc(dbptr->records, dbptr->length + 1);
    if (new_records == NULL) {
        return;
    }
    dbptr->records = new_records;
    new_record_from_command(new_records + dbptr->length, command);
    return;
}


void
process_one_command(Databaseptr dbptr, char const *argv) {
    Command command = parse_command(argv);
    switch (command.c) {
    case 'g' :
        /* code */
        process_get(dbptr, &command);
        break;
    case 'p' :
        process_put(dbptr, &command);
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


int 
main(int argc, char const *argv[])
{

    Database *dbptr = malloc(sizeof(Database));
    if (dbptr == NULL) {
        return -1;
    }
    read_database(dbptr);
    if (dbptr == NULL) {
        return -1;
    } 
    while (true) {
        
    }
    printf("argc = %d\n", argc);
    for(int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
        // printf("%c\n", command.c);
        // printf("%d\n", command.key);
        // printf("%s\n", command.value);
        process_one_command(dbptr, argv[i]);
    }
    write_database(dbptr);    
    return 0;
}

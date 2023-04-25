#include "kvlib.h"
#include <string.h>
#include <stdio.h>



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
new_record_from_command(Recordptr recordptr, Command *command) {
    if (recordptr == NULL) {
        return;
    }
    recordptr->deleted = false;
    recordptr->key = command->key;
    recordptr->length = strlen(command->value);
    String string = malloc(sizeof(char) * (recordptr->length + 1));
    if (string == NULL) {
        return;
    }
    recordptr->value = string;
    return;
}
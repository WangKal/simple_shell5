#include "alias.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIAS_NAME_LENGTH 100
#define MAX_ALIAS_VALUE_LENGTH 100

/* Structure to represent an alias */
typedef struct {
    char name[MAX_ALIAS_NAME_LENGTH];
    char value[MAX_ALIAS_VALUE_LENGTH];
} Alias;

/* Maximum number of aliases */
#define MAX_ALIASES 100

/* Array to store aliases */
Alias alias_table[MAX_ALIASES];

/* Number of aliases currently defined */
int num_aliases = 0;

/* Initialize the alias table */
void init_alias_table() {
    num_aliases = 0;
}

/* Print all aliases */
void print_all_aliases() {
	int i;
    for (i = 0; i < num_aliases; i++) {
        printf("%s='%s'\n", alias_table[i].name, alias_table[i].value);
    }
}

/* Print specified aliases */
void print_specified_aliases(char **args) {
	int i;
	int j;
    for (i = 1; args[i] != NULL; i++) {
        for (j = 0; j < num_aliases; j++) {
            if (strcmp(args[i], alias_table[j].name) == 0) {
                printf("%s='%s'\n", alias_table[j].name, alias_table[j].value);
                break;
            }
        }
    }
}

/* Define new aliases */
void define_aliases(char **args) {
	int i;
	int j;
	char *name;
	char *value;
    for (i = 1; args[i] != NULL; i++) {
        char *equal_sign = strchr(args[i], '=');
        if (equal_sign == NULL) {
            /* Alias name without a value, print error message*/
            fprintf(stderr, "Usage: alias [name[='value'] ...]\n");
            return;
        }

        *equal_sign = '\0';
	name = args[i];
        value = equal_sign + 1;

        /* Check if the alias already exists*/
        for (j = 0; j < num_aliases; j++) {
            if (strcmp(name, alias_table[j].name) == 0) {
                /*Replace the value of the existing alias*/
                strcpy(alias_table[j].value, value);
                break;
            }
        }

        /* If the alias doesn't exist, create a new one*/
        if (num_aliases < MAX_ALIASES) {
            strcpy(alias_table[num_aliases].name, name);
            strcpy(alias_table[num_aliases].value, value);
            num_aliases++;
        }
    }
}

/* Execute the alias builtin command */
int execute_builtin_alias(char **args) {
    if (args[1] == NULL) {
        /* No arguments, print all aliases*/
        print_all_aliases();
    } else if (args[1][0] == '=') {
        /* Invalid alias name starting with '='*/
        fprintf(stderr, "Invalid alias name\n");
    } else if (strchr(args[1], '=') != NULL) {
        /* Define new aliases*/
        define_aliases(args);
    } else {
        /* Print specified aliases*/
        print_specified_aliases(args);
    }

    return 0; /* BUILTIN_SUCCESS*/
}


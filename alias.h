#ifndef ALIAS_H
#define ALIAS_H

/* Initialize the alias table */
void init_alias_table();

/* Print all aliases */
void print_all_aliases();

/* Print specified aliases */
void print_specified_aliases(char **args);

/* Define new aliases */
void define_aliases(char **args);

/* Execute the alias builtin command */
int execute_builtin_alias(char **args);

#endif /* ALIAS_H */


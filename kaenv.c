#include "shell.h"

/**
 * _envkangu - Prints the current environment variables.
 * @info: Pointer to a struct containing shell information.
 *
 * Return: Always 0.
 */
int _envkangu(i_t *info)
{
    p_l_str(info->env);
    return (0);
}

/**
 * _getenv - Gets the value of an environment variable.
 * @info: Pointer to a struct containing shell information.
 * @name: The environment variable name.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *_getenv(i_t *info, const char *name)
{
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = with_starts(node->str, name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * _setenvkangu - Initialize a new environment variable or modify an existing one.
 * @info: Pointer to a struct containing shell information.
 *
 * Return: Always 0.
 */
int _setenvkangu(i_t *info)
{
    if (info->argc != 3)
    {
        _ep("Incorrect number of arguments\n");
        return (1);
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * _myunsetenv - Remove an environment variable.
 * @info: Pointer to a struct containing shell information.
 *
 * Return: Always 0.
 */
int _myunsetenv(i_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _ep("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        _unsetenvkangu(info, info->argv[i]);

    return (0);
}

/**
 * p_e_l - Populates the environment linked list.
 * @info: Pointer to a struct containing shell information.
 *
 * Return: Always 0.
 */
int p_e_l(i_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}

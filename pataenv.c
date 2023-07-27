#include "shell.h"

/**
 * get_environ - Returns the copy of our environment as a string array.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *
 * Return: Pointer to the string array representing the environment.
 */
char **get_environ(i_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = l_to_strings(info->env);
        info->env_changed = 0;
    }

    return (info->environ);
}

/**
 * _unsetenvkangu - Removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string representing the environment variable to be removed.
 *
 * Return: 1 if the variable is deleted, 0 otherwise.
 */
int _unsetenvkangu(i_t *info, char *var)
{
    l_t *node = info->env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = with_starts(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), i);
            i = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (info->env_changed);
}

/**
 * _setenv - Initializes a new environment variable or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The string representing the environment variable name.
 * @value: The string representing the environment variable value.
 *
 * Return: Always 0.
 */
int _setenv(i_t *info, char *var, char *value)
{
    char *buf = NULL;
    l_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(_lenstr(var) + _lenstr(value) + 2);
    if (!buf)
        return (1);
    _cpystr(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = with_starts(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}

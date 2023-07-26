#include "shell1.h"

/**
 * custom_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int custom_history(ShellInfo *info)
{
    print_string_list(info->history);
    return (0);
}

/**
 * unset_custom_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_custom_alias(ShellInfo *info, char *str)
{
    char *p, c;
    int ret;

    p = custom_strchr(str, '=');
    if (!p)
        return (1);
    c = *p;
    *p = 0;
    ret = delete_node_at_index(&(info->alias),
        get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
    *p = c;
    return (ret);
}

/**
 * set_custom_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_custom_alias(ShellInfo *info, char *str)
{
    char *p;

    p = custom_strchr(str, '=');
    if (!p)
        return (1);
    if (!*++p)
        return (unset_custom_alias(info, str));

    unset_custom_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_custom_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_custom_alias(StringList *node)
{
    char *p = NULL, *a = NULL;

    if (node)
    {
        p = custom_strchr(node->str, '=');
        for (a = node->str; a <= p; a++)
            custom_putchar(*a);
        custom_putchar('\'');
        custom_puts(p + 1);
        custom_puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * custom_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int custom_alias(ShellInfo *info)
{
    int i = 0;
    char *p = NULL;
    StringList *node = NULL;

    if (info->arg_count == 1)
    {
        node = info->alias;
        while (node)
        {
            print_custom_alias(node);
            node = node->next;
        }
        return (0);
    }
    for (i = 1; info->arg_values[i]; i++)
    {
        p = custom_strchr(info->arg_values[i], '=');
        if (p)
            set_custom_alias(info, info->arg_values[i]);
        else
            print_custom_alias(node_starts_with(info->alias, info->arg_values[i], '='));
    }

    return (0);
}

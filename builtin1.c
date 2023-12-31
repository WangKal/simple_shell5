#include "shell.h"

/**
 * historia - Display the history list, one command per line, preceded
 *            with line numbers starting at 0.
 * @info: Pointer to a struct containing shell information.
 *
 * Return: Always 0.
 */
int historia(i_t *info)
{
	p_l(info->history);
	return (0);
}

/**
 * unset_alias - Unset an alias.
 * @info: Pointer to a struct containing shell information.
 * @str: The alias string.
 *
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(i_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _chrstr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		g_n_i(info->alias, node_with_starts(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Set an alias to a string.
 * @info: Pointer to a struct containing shell information.
 * @str: The alias string.
 *
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(i_t *info, char *str)
{
	char *p;

	p = _chrstr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - Print an alias string.
 * @node: Pointer to the alias node.
 *
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(l_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _chrstr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - Mimics the alias builtin (man alias).
 * @info: Pointer to a struct containing shell information.
 *
 * Return: Always 0.
 */
int _myalias(i_t *info)
{
	int i = 0;
	char *p = NULL;
	l_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _chrstr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_with_starts(info->alias, info->argv[i], '='));
	}

	return (0);
}

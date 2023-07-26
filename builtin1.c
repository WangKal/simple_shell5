#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @in: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(i *in)
{
	print_list(in->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @in: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(i *in, char *s)
{
	char *p, c;
	int ret;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(in->alias),
		g_n_i(in->alias, node_with_start(in->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @in: parameter struct
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(i *in, char *s)
{
	char *p;

	p = _strchr(s, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(in, s));

	unset_alias(in, s);
	return (a_n_e(&(in->alias), s, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(kalist_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_sput(p + 1);
		_sput("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(i_t *info)
{
	int i = 0;
	char *p = NULL;
	kalist_t *node = NULL;

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
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_with_start(info->alias, info->argv[i], '='));
	}

	return (0);
}

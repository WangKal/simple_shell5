#include "shell.h"

/**
 * is_chain - Tests if the current char in the buffer is a chain delimiter.
 * @info: The parameter struct.
 * @buf: The char buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if chain delimiter, 0 otherwise.
 */
int is_chain(i_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * c_c - Checks if we should continue chaining based on last status.
 * @info: The parameter struct.
 * @buf: The char buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void c_c(i_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - Replaces an alias in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_alias(i_t *info)
{
	int i;
	l_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_with_starts(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _chrstr(node->str, '=');
		if (!p)
			return (0);
		p = _upstrd(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * r_v - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int r_v(i_t *info)
{
	int i = 0;
	l_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_cmpstr(info->argv[i], "$?"))
		{
			r_s(&(info->argv[i]),
				_upstrd(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_cmpstr(info->argv[i], "$$"))
		{
			r_s(&(info->argv[i]),
				_upstrd(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_with_starts(info->env, &info->argv[i][1], '=');
		if (node)
		{
			r_s(&(info->argv[i]),
				_upstrd(_chrstr(node->str, '=') + 1));
			continue;
		}
		r_s(&info->argv[i], _upstrd(""));

	}
	return (0);
}

/**
 * r_s - Replaces string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int r_s(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

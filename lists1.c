#include "shell.h"

/**
 * len_list - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t len_list(const kalist_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * kalist_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **kalist_to_strings(kalist_t *head)
{
	kalist_t *node = head;
	size_t i = len_list(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_lenstr(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _cpystr(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a kalist_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const kalist_t *h)
{
	size_t i = 0;

	while (h)
	{
		_sput(c_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_sput(h->str ? h->str : "(nil)");
		_sput("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_with_start - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
kalist_t *node_with_start(kalist_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = with_start(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * g_n_i - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t g_n_i(kalist_t *head, kalist_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

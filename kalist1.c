#include "shell.h"

/**
 * l_l - Determines the length of a linked list.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t l_l(const list_t *h)
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
 * list_to_strings - Converts a linked list of strings to an array of strings.
 * @head: Pointer to the first node.
 *
 * Return: Array of strings or NULL on failure.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = l_l(head), j;
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
 * p_l - Prints all elements of a linked list of type list_t.
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t p_l(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_with_starts - Returns a node whose string starts with the given prefix and character.
 * @node: Pointer to the list head.
 * @prefix: String to match as a prefix.
 * @c: The next character after the prefix to match.
 *
 * Return: The matching node or NULL if no match found.
 */
list_t *node_with_starts(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = with_starts(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * g_n_i - Gets the index of a node in a linked list.
 * @head: Pointer to the list head.
 * @node: Pointer to the node.
 *
 * Return: The index of the node or -1 if not found.
 */
ssize_t g_n_i(list_t *head, list_t *node)
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

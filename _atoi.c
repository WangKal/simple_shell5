#include "shell.h"

/**
 * interactive - true if in interactive mode
 * @in: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(i *in)
{
	return (isatty(STDIN_FILENO) && in->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @a: the char to check
 * @dl: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char a, char *dl)
{
	while (*dl)
		if (*dl++ == a)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@b: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int b)
{
	if ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@p: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *p)
{
	int i, sign = 1, bendera = 0, jibu;
	unsigned int result = 0;

	for (i = 0;  p[i] != '\0' && bendera!= 2; i++)
	{
		if (p[i] == '-')
			sign *= -1;

		if (p[i] >= '0' && p[i] <= '9')
		{
			bendera = 1;
			result *= 10;
			result += (p[i] - '0');
		}
		else if (bendera == 1)
			bendera = 2;
	}

	if (sign == -1)
		jibu = -result;
	else
		jibu = result;

	return (jibu);
}


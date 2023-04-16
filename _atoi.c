#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @j: the char to check
 * @delimm: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char j, char *delimm)
{
	while (*delimm)
		if (*delimm++ == j)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @j: The character to input
 * Return: 1 if j is alphabetic, 0 otherwise
 */

int _isalpha(int j)
{
	if ((j >= 'a' && j <= 'z') || (j >= 'A' && j <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @p: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *p)
{
	int l, signs = 1, flags = 0, output;
	unsigned int results = 0;

	for (l = 0; p[l] != '\0' && flags != 2; l++)
	{
		if (p[l] == '-')
			signs *= -1;

		if (p[l] >= '0' && p[l] <= '9')
		{
			flags = 1;
			results *= 10;
			results += (p[l] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (signs == -1)
		output = -results;
	else
		output = results;

	return (output);
}

#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int a, k, l, n, numword = 0;
	char **v;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			numword++;

	if (numword == 0)
		return (NULL);
	v = malloc((1 + numword) * sizeof(char *));
	if (!v)
		return (NULL);
	for (a = 0, k = 0; k < numword; k++)
	{
		while (is_delim(str[a], d))
			a++;
		l = 0;
		while (!is_delim(str[a + l], d) && str[a + l])
			l++;
		v[k] = malloc((l + 1) * sizeof(char));
		if (!s[k])
		{
			for (l = 0; l < k; l++)
				free(v[l]);
			free(v);
			return (NULL);
		}
		for (n = 0; n < l; n++)
			v[k][n] = str[a++];
		v[k][n] = 0;
	}
	v[k] = NULL;
	return (v);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int a, k, l, m, numword = 0;
	char **v;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numword++;
	if (numword == 0)
		return (NULL);
	v = malloc((1 + numword) * sizeof(char *));
	if (!v)
		return (NULL);
	for (a = 0, k = 0; k < numword; k++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		l = 0;
		while (str[a + l] != d && str[a + l] && str[a + l] != d)
			l++;
		v[k] = malloc((l + 1) * sizeof(char));
		if (!v[k])
		{
			for (l = 0; l < k; l++)
				free(v[l]);
			free(v);
			return (NULL);
		}
		for (m = 0; m < l; m++)
			v[k][m] = str[a++];
		v[k][m] = 0;
	}
	v[k] = NULL;
	return (v);
}

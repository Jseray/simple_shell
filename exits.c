#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int p, k;
	char *j = dest;

	p = 0;
	while (src[p] != '\0' && p < n - 1)
	{
		dest[p] = src[p];
		p++;
	}
	if (p < n)
	{
		k = p;
		while (k < n)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (j);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int p, k;
	char *j = dest;

	p = 0;
	k = 0;
	while (dest[p] != '\0')
		p++;
	while (src[k] != '\0' && k < n)
	{
		dest[p] = src[k];
		p++;
		k++;
	}
	if (k < n)
		dest[p] = '\0';
	return (j);
}

/**
 **_strchr - locates a character in a string
 *@j: the string to be parsed
 *@m: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *j, char m)
{
	do {
		if (*j == m)
			return (j);
	} while (*j++ != '\0');

	return (NULL);
}

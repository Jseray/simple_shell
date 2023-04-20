#include "shell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - returns an array of strings of the list->strr
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node1 = head;
	size_t a = list_len(head), k;
	char **strs1;
	char *strr;

	if (!head || !a)
		return (NULL);
	strs1 = malloc(sizeof(char *) * (a + 1));
	if (!strs1)
		return (NULL);
	for (a = 0; node1; node1 = node1->next, a++)
	{
		strr = malloc(_strlen(node1->strr) + 1);
		if (!strr)
		{
			for (k = 0; k < a; jk++)
				free(strs1[k]);
			free(strs1);
			return (NULL);
		}

		strr = _strcpy(strr, node1->strr);
		strs1[a] = strr;
	}
	strs1[a] = NULL;
	return (strs1);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *pp = NULL;

	while (node)
	{
		pp = starts_with(node->str, prefix);
		if (pp && ((c == -1) || (*pp == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}

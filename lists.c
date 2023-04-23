#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head0;

	if (!head)
		return (NULL);
	new_head0 = malloc(sizeof(list_t));
	if (!new_head0)
		return (NULL);
	_memset((void *)new_head0, 0, sizeof(list_t));
	new_head0->num = num;
	if (str)
	{
		new_head0->str = _strdup(str);
		if (!new_head0->str)
		{
			free(new_head0);
			return (NULL);
		}
	}
	new_head0->next = *head;
	*head = new_head0;
	return (new_head0);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node0, *node1;

	if (!head)
		return (NULL);

	node1 = *head;
	new_node0 = malloc(sizeof(list_t));
	if (!new_node0)
		return (NULL);
	_memset((void *)new_node0, 0, sizeof(list_t));
	new_node0->num = num;
	if (str)
	{
		new_node0->str = _strdup(str);
		if (!new_node0->str)
		{
			free(new_node0);
			return (NULL);
		}
	}
	if (node1)
	{
		while (node1->next)
			node1 = node1->next;
		node1->next = new_node0;
	}
	else
		*head = new_node0;
	return (new_node0);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node1, *prev_node0;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node1 = *head;
		*head = (*head)->next;
		free(node1->str);
		free(node1);
		return (1);
	}
	node1 = *head;
	while (node1)
	{
		if (a == index)
		{
			prev_node0->next = node1->next;
			free(node1->str);
			free(node1);
			return (1);
		}
		a++;
		prev_node0 = node1;
		node1 = node1->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node1, *next_nodes, *head1;

	if (!head_ptr || !*head_ptr)
		return;
	head1 = *head_ptr;
	node1 = head1;
	while (node1)
	{
		next_nodes = node1->next;
		free(node1->str);
		free(node1);
		node1 = next_nodes;
	}
	*head_ptr = NULL;
}

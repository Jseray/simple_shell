#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node1 = info->env;
	size_t a = 0;
	char *pp;

	if (!node1 || !var)
		return (0);

	while (node1)
	{
		pp = starts_with(node1->str, var);
		if (pp && *pp == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			node1 = info->env;
			continue;
		}
		node1 = node1->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *  or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node1;
	char *pp;

	if (!var || !value)
		return (0);

	buff = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, var);
	_strcat(buff, "=");
	_strcat(buff, value);
	node1 = info->env;
	while (node1)
	{
		pp = starts_with(node1->str, var);
		if (pp && *pp == '=')
		{
			free(node1->str);
			node1->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node1 = node1->next;
	}
	add_node_end(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}

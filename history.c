#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buff, *dirr;

	dirr = _getenv(info, "HOME=");
	if (!dirr)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dirr) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dirr);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fdd;
	char *filename0 = get_history_file(info);
	list_t *node1 = NULL;

	if (!filename0)
		return (-1);

	fdd = open(filename0, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename0);
	if (fdd == -1)
		return (-1);
	for (node1 = info->history; node1; node1 = node1->next)
	{
		_putsfd(node1->str, fdd);
		_putfd('\n', fdd);
	}
	_putfd(BUF_FLUSH, fdd);
	close(fdd);
	return (1);
}

/**
 * read_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int a, lasts = 0, linecounts = 0;
	ssize_t fdd, rdleng, fsizes = 0;
	struct stat st;
	char *buff = NULL, *filename0 = get_history_file(info);

	if (!filename0)
		return (0);

	fdd = open(filename0, O_RDONLY);
	free(filename0);
	if (fdd == -1)
		return (0);
	if (!fstat(fdd, &st))
		fsizes = st.st_size;
	if (fsizes < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsizes + 1));
	if (!buff)
		return (0);
	rdleng = read(fdd, buff, fsizes);
	buff[fsizes] = 0;
	if (rdleng <= 0)
		return (free(buff), 0);
	close(fdd);
	for (a = 0; a < fsizes; a++)
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			build_history_list(info, buff + lasts, linecounts++);
			lasts = a + 1;
		}
	if (lasts != a)
		build_history_list(info, buff + lasts, linecounts++);
	free(buff);
	info->histcount = linecounts;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node1 = NULL;

	if (info->history)
		node1 = info->history;
	add_node_end(&node1, buf, linecount);

	if (!info->history)
		info->history = node1;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node1 = info->history;
	int a = 0;

	while (node1)
	{
		node1->num = a++;
		node1 = node1->next;
	}
	return (info->histcount = a);
}


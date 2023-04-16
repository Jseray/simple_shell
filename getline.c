#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t t = 0;
	size_t len_pp = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		t = getline(buf, &len_pp, stdin);
#else
		t = _getline(info, buf, &len_pp);
#endif
		if (t > 0)
		{
			if ((*buf)[t - 1] == '\n')
			{
				(*buf)[t - 1] = '\0'; /* remove trailing newline */
				t--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = t;
				info->cmd_buf = buf;
			}
		}
	}
	return (t);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t a, d, leng;
	ssize_t t = 0;
	char **buf_p = &(info->arg), *i;

	_putchar(BUF_FLUSH);
	t = input_buf(info, &buf, &leng);
	if (t == -1) /* EOF */
		return (-1);
	if (leng) /* we have commands left in the chain buffer */
	{
		d = a; /* init new iterator to current buf position */
		i = buf + a; /* get pointer for return */

		check_chain(info, buf, &d, a, leng);
		while (d < leng) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &d))
				break;
			d++;
		}

		a = d + 1; /* increment past nulled ';'' */
		if (a >= leng) /* reached end of buffer? */
		{
			a = leng = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = i; /* pass back pointer to current command position */
		return (_strlen(i)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (t); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: t
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t t = 0;

	if (*i)
		return (0);
	t = read(info->readfd, buf, READ_BUF_SIZE);
	if (t >= 0)
		*i = t;
	return (t);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: j
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, leng;
	size_t k;
	ssize_t t = 0, j = 0;
	char *pp = NULL, *new_pp = NULL, *o;

	pp = *ptr;
	if (pp && length)
		j = *length;
	if (a == leng)
		a = leng = 0;

	t = read_buf(info, buf, &leng);
	if (t == -1 || (t == 0 && leng == 0))
		return (-1);

	o = _strchr(buf + a, '\n');
	k = o ? 1 + (unsigned int)(o - buf) : leng;
	new_pp = _realloc(pp, j, j ? j + k : k + 1);
	if (!new_pp) /* MALLOC FAILURE! */
		return (pp ? free(pp), -1 : -1);

	if (j)
		_strncat(new_pp, buf + a, k - a);
	else
		_strncpy(new_pp, buf + a, k - a + 1);

	j += k - a;
	a = k;
	pp = new_pp;

	if (length)
		*length = j;
	*ptr = pp;
	return (j);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

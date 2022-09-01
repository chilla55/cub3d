/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:50:38 by skorte            #+#    #+#             */
/*   Updated: 2021/10/20 18:30:19 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Searches the bufferlist for the file descriptor fd
** and returns the corresponding list element.
** Creates a new element if none for fd is found.
*/

static t_fd_buffer	*gnl_search_fd_buffer(int fd, t_fd_buffer **bufferlist)
{
	t_fd_buffer	**fd_buffer;

	fd_buffer = bufferlist;
	while (*fd_buffer)
	{
		if ((*fd_buffer)->fd == fd)
			return (*fd_buffer);
		else
			fd_buffer = &(*fd_buffer)->next;
	}
	(*fd_buffer) = malloc(sizeof(t_fd_buffer));
	(*fd_buffer)->fd = fd;
	(*fd_buffer)->buffer = NULL;
	(*fd_buffer)->next = NULL;
	return ((*fd_buffer));
}

/*
** Reads at max BUFFER_SIZE bytes from fd,
** appends them to fd_buffer->buffer.
** Returns number of read bytes.
** File end reached if readbytes < BUFFER_SIZE
*/

static int	gnl_read(int fd, t_fd_buffer *fd_buffer)
{
	int		readbytes;
	char	*output;

	readbytes = 0;
	output = gnl_strdup(fd_buffer->buffer);
	if (fd_buffer->buffer)
		free(fd_buffer->buffer);
	fd_buffer->buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	readbytes = read(fd, fd_buffer->buffer, BUFFER_SIZE);
	fd_buffer->buffer[readbytes] = '\0';
	fd_buffer->buffer = gnl_strjoin(output, fd_buffer->buffer);
	return (readbytes);
}

/*
** Checks how to generate an output string.
**
** If the buffer is empty or NULL, it tries to read from the fd with gnl_read.
** If the buffer is not empty, but does not contain a newline,
** it also calls gnl_read to add more from fd to the buffer.
**
** If it now reaches a newline, a splits the buffer into new buffer and output.
**
** If not, it keeps the buffer and starts get_new_line again, to recursively
** fill the buffer till either a newline or the end of file are reached.
*/

static char	*gnl_generate_output(int fd, t_fd_buffer **fd_buffer, char *output)
{
	int	readbytes;

	if (!(*fd_buffer)->buffer)
		readbytes = gnl_read(fd, (*fd_buffer));
	else if (!gnl_strchr((*fd_buffer)->buffer, '\n'))
		readbytes = gnl_read(fd, (*fd_buffer));
	output = gnl_strdup((*fd_buffer)->buffer);
	if ((*fd_buffer)->buffer)
		free((*fd_buffer)->buffer);
	(*fd_buffer)->buffer = gnl_strchr(output, '\n');
	if ((*fd_buffer)->buffer)
	{
		(*fd_buffer)->buffer[0] = '\0';
		(*fd_buffer)->buffer++;
		(*fd_buffer)->buffer = gnl_strdup((*fd_buffer)->buffer);
		output = gnl_straddchar(output, '\n');
	}
	else if (readbytes == BUFFER_SIZE)
	{
		(*fd_buffer)->buffer = gnl_strdup(output);
		if (output)
			free(output);
		output = get_next_line(fd);
	}
	return (output);
}

/*
** Sanitizes the bufferlist if the buffer for fd is empty.
**
** To find the right list element, the function calls itself
** for the next list element till the fd_buffer is found.
** The fd_buffer list element is freed and the bufferlist reconnected.
*/

void	gnl_sanitize_buffer(int fd, t_fd_buffer **bufferlist)
{
	t_fd_buffer	*temp;

	if (!*bufferlist)
		return ;
	if ((*bufferlist)->fd == fd && !(*bufferlist)->buffer)
	{
		temp = (*bufferlist)->next;
		free (*bufferlist);
		(*bufferlist) = temp;
		return ;
	}
	gnl_sanitize_buffer(fd, &(*bufferlist)->next);
}

/*
** Reads BUFFER_SIZE bytes from the file descriptor fd
** until it reaches a newline or end of file
** Returns the line as string and stores the rest in a static buffer
*/

char	*get_next_line(int fd)
{
	char				*output;
	static t_fd_buffer	*bufferlist;
	t_fd_buffer			*fd_buffer;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) == -1)
		return (NULL);
	fd_buffer = gnl_search_fd_buffer(fd, &bufferlist);
	output = NULL;
	output = gnl_generate_output(fd, &fd_buffer, output);
	gnl_sanitize_buffer(fd, &bufferlist);
	if (!output[0])
	{
		free(output);
		return (NULL);
	}
	return (output);
}

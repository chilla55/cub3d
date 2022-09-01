/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:51:02 by skorte            #+#    #+#             */
/*   Updated: 2021/10/20 18:23:37 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

/*
// if called multiple times in the project, it  will not be processed again
*/

# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

/*
** stdlib: malloc, free
** unistd: read
*/

typedef struct fd_buffer
{
	int					fd;
	char				*buffer;
	struct fd_buffer	*next;
}				t_fd_buffer;

/*
** default buffer size
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
int		gnl_strlen(const char *s);
char	*gnl_strdup(const char *s);
char	*gnl_straddchar(char *src, char c);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);

#endif
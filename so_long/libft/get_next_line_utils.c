/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skorte <skorte@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:50:38 by skorte            #+#    #+#             */
/*   Updated: 2021/10/20 17:53:54 by skorte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** gnl_strlen(s) returns the number of characters of a string s.
** It returns 0 for NULL strings
*/

int	gnl_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
** The strdup() function returns a pointer to a new string which is
** a duplicate of the string s.  Memory for the new string is
** obtained with malloc(3), and can be freed with free(3).
** On success, the strdup() function returns a pointer to the
** duplicated string.  It returns NULL if insufficient memory was
** available.
*/

char	*gnl_strdup(const char *s)
{
	char	*dst;
	int		size;
	int		i;

	if (s == NULL)
		return (NULL);
	size = gnl_strlen(s);
	dst = malloc((size + 1) * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		dst[i] = s[i];
		i++;
	}
	return (dst);
}

/*
** gnl_straddchar adds the character c to the end of a string.
** It allocates new memory for the longer string with malloc
** and frees the old memory with free.
** It then returns a pointer to the new string.
*/

char	*gnl_straddchar(char *src, char c)
{
	char	*dst;
	int		size;
	int		i;

	if (src == NULL)
		return (NULL);
	size = gnl_strlen(src) + 1;
	dst = malloc((size + 1) * sizeof(char));
	if (dst == NULL)
		return (dst);
	i = 0;
	while (i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = c;
	dst[size] = '\0';
	free(src);
	return (dst);
}

/*
** The strchr() function returns a pointer to the first occurrence
** of the character c in the string s or NULL if the character is not found.
** The terminating null byte is considered part of the string, so that
** if c is specified as '\0', this function returns a pointer to the terminator.
*/

char	*gnl_strchr(const char *s, int c)
{
	while (*s)
	{
		if (s[0] == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

/*
** Allocates (with malloc(3)) and returns a new
** string, which is the result of the concatenation
** of ’s1’ and ’s2’. Frees 's1' and 's2' afterwards.
*/

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	dest = malloc((gnl_strlen(s1) + gnl_strlen(s2) + 1) * sizeof(char));
	if (dest == NULL)
		return (dest);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[i - gnl_strlen(s1)])
	{
		dest[i] = s2[i - gnl_strlen(s1)];
		i++;
	}
	dest[i] = '\0';
	free(s1);
	free(s2);
	return (dest);
}

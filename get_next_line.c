/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:21:33 by ielyatim          #+#    #+#             */
/*   Updated: 2024/11/17 17:14:30 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	str_len;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start > str_len)
		return (ft_strdup(""));
	i = 0;
	while (i < len && s[start + i])
		i++;
	str = malloc(i + 1);
	if (str)
	{
		i = 0;
		while (i < len && s[start + 1])
			str[i++] = s[start++];
		str[i] = '\0';
	}
	return (str);
}

static char	*ft_strchr(const char *s, int c)
{
	while (*s != 0)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

static char	*get_new_line(char **stash)
{
	char	*line;
	size_t	newline_index;
	char	*tmp;

	newline_index = ft_strchr(*stash, '\n') - *stash;
	line = ft_substr(*stash, 0, newline_index + 1);
	tmp = ft_strdup(*stash + newline_index + 1);
	free(*stash);
	*stash = tmp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*tmp;
	char		*buffer;
	ssize_t		bytes_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = NULL;
	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(stash, buffer);
		free(stash);
		stash = tmp;
	}
	if (stash && *stash)
	{
		if (ft_strchr(stash, '\n'))
			line = get_new_line(&stash);
		else
		{
			line = ft_strdup(stash);
			free(stash);
			stash = NULL;
		}
	}
	free(buffer);
	return (line);
}

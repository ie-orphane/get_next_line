/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:21:33 by ielyatim          #+#    #+#             */
/*   Updated: 2024/11/17 10:48:51 by ielyatim         ###   ########.fr       */
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

char	*ft_strchr(const char *s, int c)
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

static int	ft_strindex(const char *s, int c)
{
	int	i;

	if (s)
	{
		i = 0;
		while (s[i])
		{
			if (s[i] == c)
				return (i);
			i++;
		}
		if (s[i] == c && c == '\0')
			return (i);
	}
	return (-1);
}

static char	*get_new_line(char **stash)
{
	char	*line;
	char	*tmp;
	int		index;
	
	index = ft_strindex(*stash, '\n');
	line = NULL;
	if (index != -1)
	{
		line = ft_substr(*stash, 0, index + 1);
		tmp = ft_substr(*stash, index + 1, ft_strlen(*stash));
		free(*stash);
		*stash = tmp;
	}
	return (line);
}

static void	fill_stash(char **stash, const char *buffer, ssize_t nb)
{
	char	*tmp;

	if (*stash)
	{
		tmp = ft_substr(buffer, 0, nb);
		*stash = ft_strjoin(*stash, tmp);
		free(tmp);
	}
	else
		*stash = ft_strdup(buffer);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*line;
	ssize_t		nb;

	line = NULL;
	buffer = malloc(BUFFER_SIZE * sizeof(char));
	while (!line)
	{
		nb = read(fd, buffer, BUFFER_SIZE);
		if (nb < 0)
			break ;
		if (nb == 0 && !stash)
			break ;
		if (nb == 0 && stash)
		{
			line = get_new_line(&stash);
			if (!line)
			{
				line = ft_substr(stash, 0, ft_strlen(stash));
				free(stash);
				stash = NULL;
			}
			break ;
		}
		fill_stash(&stash, buffer, nb);
		line = get_new_line(&stash);
	}
	free(buffer);
	return (line);
}

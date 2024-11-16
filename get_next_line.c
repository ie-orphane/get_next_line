/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:21:33 by ielyatim          #+#    #+#             */
/*   Updated: 2024/11/16 11:23:32 by ielyatim         ###   ########.fr       */
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
		while (i < len && s[start])
			str[i++] = s[start++];
		str[i] = '\0';
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char		buffer[5];
	static char	*stash;
	char		*line;
	ssize_t		nb;

	line = NULL;
	while (!line)
	{
		nb = read(fd, buffer, 5) + 1;
		if (nb == 1)
			return (NULL);
		if (stash)
			stash = ft_strjoin(stash, buffer);
		else
			stash = ft_strdup(buffer);
		while (--nb && !line)
		{
			if (buffer[5 - nb] == '\n')
			{
				line = ft_substr(stash, 0, ft_strlen(stash) - nb + 1);
				free(stash);
				stash = ft_substr(buffer, 5 - nb + 1, nb - 1);
			}
		}
	}
	return (line);
}

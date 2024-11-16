/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:21:30 by ielyatim          #+#    #+#             */
/*   Updated: 2024/11/16 10:10:36 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	int		len;
	int		i;

	len = 0;
	while (s1[len])
		len++;
	ptr = malloc(len + 1);
	if (ptr != NULL)
	{
		i = 0;
		while (i < len)
		{
			ptr[i] = s1[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = malloc(count * size);
	if (ptr)
	{
		i = 0;
		while (i < count * size)
			ptr[i++] = 0;
	}
	return (ptr);
}

static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!dst && size == 0)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (dst_len >= size)
		return (size + src_len);
	j = 0;
	i = dst_len;
	while (src[j] && j < (size - dst_len - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (src_len + dst_len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;
	size_t	str_size;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_size = s1_len + s2_len + 1;
	if (s1_len + s2_len == 0)
		return ((char *)ft_calloc(1, 1));
	str = malloc(str_size);
	if (str)
	{
		str[0] = '\0';
		ft_strlcat(str, s1, str_size);
		ft_strlcat(str, s2, str_size);
	}
	return (str);
}

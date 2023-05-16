/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:35:22 by zdevove           #+#    #+#             */
/*   Updated: 2023/01/03 09:17:33 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ftt_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		j;
	int		i;

	i = 0;
	j = 0;
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s1 && s1[i] != '\0')
		str[j++] = s1[i++];
	i = 0;
	while (s2 && s2[i] != '\0')
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ftt_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == (unsigned char)c)
			return ((char *)str + i + 1);
		i++;
	}
	if (str[i] == (unsigned char)c)
		return ((char *)str + i);
	return (0);
}

size_t	ftt_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if (srclen + 1 < size)
	{
		while (i < srclen)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	else if (size != 0)
	{
		while (i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[size - 1] = '\0';
	}
	return (srclen);
}

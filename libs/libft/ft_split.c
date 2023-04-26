/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:17:44 by zdevove           #+#    #+#             */
/*   Updated: 2022/11/11 12:58:06 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_count(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static char	*get_word(char *str, char c)
{
	char	*dst;
	int		len;
	int		j;

	j = 0;
	len = 0;
	while (str[len] != '\0' && str[len] != c)
		len++;
	dst = (char *)malloc((len + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (j < len)
	{
		dst[j] = str[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		j;
	int		i;
	int		size;

	if (!s)
		return (0);
	i = 0;
	j = 0;
	size = get_count((char *)s, c);
	tab = (char **)malloc((size + 1) * sizeof(char *));
	if (!tab)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			tab[j++] = get_word((char *)s + i, c);
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	tab[j] = 0;
	return (tab);
}

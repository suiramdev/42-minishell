/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:15:57 by zdevove           #+#    #+#             */
/*   Updated: 2022/11/16 14:33:29 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t x, size_t y)
{
	unsigned char	*str;

	if (y > 0 && x * y / y != x)
		return (0);
	str = malloc(x * y);
	if (!str)
		return (0);
	ft_bzero(str, x * y);
	return (str);
}

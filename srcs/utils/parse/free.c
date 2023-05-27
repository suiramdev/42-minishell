/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:55:15 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/27 00:55:20 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Free tokens
/// @param tokens The tokens to free
void	free_tokens(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

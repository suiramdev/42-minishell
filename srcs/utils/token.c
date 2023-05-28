/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:50:49 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/28 18:23:10 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_split(char **tokens, size_t *i, bool *split_token, int k)
{
	char	**new_tokens;
	size_t	j;

	new_tokens = (char **)malloc(sizeof(char *) * (k + 2));
	if (!new_tokens)
		return (0);
	j = -1;
	while (j++ < (*i) - 1)
		new_tokens[j] = tokens[j];
	k = 0;
	while (tokens[(*i) - 1][k] != ' ')
		k++;
	new_tokens[j++] = ft_substr(tokens[(*i) - 1], 0, k);
	new_tokens[j] = ft_strdup(tokens[(*i) - 1] + k + 1);
	free(tokens[(*i) - 1]);
	free(tokens);
	(*i)++;
	*split_token = false;
	return (new_tokens);
}

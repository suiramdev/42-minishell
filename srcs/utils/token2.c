/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:50:49 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/24 16:50:51 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	isquotefill(char *quote, char c)
{
	if (!(*quote))
		(*quote) = c;
}

/// @brief Check if a command token string contains any special characters.
/// @param c The character to check.
/// @return 1 if the character is special, 0 otherwise.
bool	special_char(char c)
{
	return (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || (c == '_')));
}

void	unexpected_token_error(char *token)
{
	ft_putstr_fd("unexpected token `", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
}

int	unexpected_token(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (((!ft_strncmp(tokens[i], ">", 1) || !ft_strncmp(tokens[i], "<", 1))
				&& !tokens[i + 1]) || (!ft_strncmp(tokens[i], "|", 1)
				&& (!tokens[i + 1] || !tokens[i + 1][0]))
				|| (!ft_strncmp(tokens[0], "|", 1)))
			return (unexpected_token_error(tokens[i]), 0);
		if ((!ft_strncmp(tokens[i], ">", 1) || !ft_strncmp(tokens[i], "<", 1))
			&& tokens[i + 1] && (!ft_strncmp(tokens[i + 1], ">", 1)
				|| !ft_strncmp(tokens[i + 1], "<", 1)
				|| !ft_strncmp(tokens[i + 1], "|", 1)))
			return (unexpected_token_error(tokens[i]), 0);
		if (!ft_strncmp(tokens[i], "|", 1) && tokens[i + 1]
			&& !ft_strncmp(tokens[i + 1], "|", 1))
			return (unexpected_token_error(tokens[i]), 0);
		i++;
	}
	return (1);
}

char	**token_split(char **tokens, size_t *i, bool *split_token, int k)
{
	char **new_tokens;
	size_t j;

	new_tokens = (char **)malloc(sizeof(char *) * (k + 2));
	if (!new_tokens)
		return (0);
	j = -1;
	while (j++ < (*i) - 1)	// copy each token dans new tokens
		new_tokens[j] = tokens[j];

	k = 0;
	while (tokens[(*i) - 1][k] != ' ')
		k++;

	new_tokens[j++] = ft_substr(tokens[(*i) - 1], 0, k); // Take the command
	new_tokens[j] = ft_strdup(tokens[(*i) - 1] + k + 1); // Take the rest

	free(tokens[(*i) - 1]); // free l'ancien token qu'est pas split
	free(tokens); // free l'ancien tokens
	(*i)++; // on a ajouter 1 token donc add 1
	*split_token = false;
	return (new_tokens);
}
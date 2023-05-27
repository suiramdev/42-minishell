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

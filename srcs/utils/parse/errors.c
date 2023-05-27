/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:36:04 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/27 16:28:46 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Print an error message when an invalid identifier is passed to a builtin command.
/// @param token The invalid identifier.
static void	error_unexpected(char *token, size_t len)
{
	char	*str;

	str = ft_substr(token, 0, len);
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	free(str);
}

static bool	check_tokens(char **tokens)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' || tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			j = 0;
			while (tokens[i][j])
				j++;
			if (j > 2)
				return (error_unexpected(tokens[i], 1
					+ (tokens[i][0] == '<' || tokens[i][0] == '>')), false);
			if (tokens[i][0] == '|'
				&& (i == 0 || !tokens[i - 1]  || tokens[i - 1][0] == '|' ))
				return (error_unexpected("|", 1), false);
			if ((tokens[i][0] == '<' || tokens[i][0] == '>') && !tokens[i + 1])
				return (error_unexpected(tokens[i], 1), false);
		}
		i++;
	}
	return (true);
}

static bool	check_newline(char **tokens)
{
	size_t	i;

	i = 0;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' || tokens[i][0] == '<' || tokens[i][0] == '>')
		{
			if (!tokens[i + 1] || (tokens[i][0] == '<' && tokens[i + 1][0] == '>'))
				return (error_unexpected("newline", 7), false);
		}
		i++;
	}
	return (true);
}

/// @brief Handle unexpected characters in a token string.
/// @param tokens The token string to check.
/// @return true if the token string is valid, false otherwise.
bool	handle_unexpected(char **tokens)
{
	if (!check_tokens(tokens))
		return (false);
	if (!check_newline(tokens))
		return (false);
	return (true);
}

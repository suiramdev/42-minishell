/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:34:15 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 16:20:06 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if the character is a space
/// @param c The character to check
/// @return true if the character is a space, false otherwise
bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

/// @brief Skip the spaces in the line
/// @param line The line to parse
/// @param inc The increment variable pointer which will be incremented by the
/// number of spaces
/// @return void
void	skip_spaces(char *line, size_t *inc)
{
	while (is_space(line[(*inc)]))
		(*inc)++;
}

/// @brief Skip the content of the quotes
/// @param line The line to parse
/// @param inc The increment variable pointer which will be incremented by the 
/// number of characters in the quote
/// @return true if the quote is closed, false otherwise
bool	handle_quotes(char *line, size_t *inc)
{
	int		i;
	char	quote;

	i = 1;
	quote = line[0];
	while (line[i] && line[i] != quote)
			i++;
	if (line[i] != quote)
		return (false);
	*inc = i + 1;
	return (true);
}

void	increase_token_index(size_t *count, size_t *i)
{
	(*count)++;
	(*i)++;
}

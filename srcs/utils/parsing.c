/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
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

/// @brief Check if the line contains pipes
/// @param str The line to check
/// @return true if the line contains pipes, false otherwise
bool	has_pipes(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
		return (false);
	while (str[i])
	{
		if (str[i] == '|')
			return (true);
		i++;
	}
	return (false);
}

bool	valid_last_command(char **tokens, size_t i)
{
	return (tokens[i][0] == '|' && tokens[i + 1][0] == '>' && !tokens[i + 3]);
}

/// @brief Set all the commands has_pipe to true
/// @param cmds The commands to set
void	cmds_has_pipes(t_cmd *cmds)
{
	t_cmd	*head;

	head = cmds;
	while (head)
	{
		head->has_pipe = true;
		head = head->next;
	}
}

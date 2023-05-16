/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:34:15 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/05 14:30:29 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Check if the character is a space
/// @param c The character to check
/// @return 1 if the character is a space, 0 otherwise
int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

void	skip_spaces(char *line, size_t *i)
{
    while (is_space(line[(*i)]))
        (*i)++;
}

int	skip_quotes(char *line)
{
	int		i;
	char	quote;

	i = 1;
	quote = line[0];
	while (line[i] && line[i] != quote)
			i++;
	if (line[i] == quote)
		return (i + 1);
	return (-1);
}

int handle_quotes(char *line, size_t *i)
{
    int skip;

    skip = skip_quotes(line + (*i));
    if (skip == -1)
        return (0);
    (*i) += skip;
    return (1);
}

void    increase_token_index(size_t *count, size_t *i)
{
    (*count)++;
    (*i)++;
}

/// @brief Check if the line contains pipes
/// @param str The line to check
/// @return 1 if the line contains pipes, 0 otherwise
int	has_pipes(char *str)
{
    int	i;

	i = 0;
	if (str[i] == '\'' || str[i] == '"')
		return (0);
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

int valid_last_command(char **tokens, int i)
{
    if (tokens[i][0] == '|' && tokens[i + 1][0] == '>' && !tokens[i + 3])
        return (0);
    return (1);
}

void	cmds_has_pipes(t_cmd *cmds)
{
	t_cmd *head;

	head = cmds;
	while (head)
	{
		head->has_pipe = 1;
		head = head->next;
	}
}
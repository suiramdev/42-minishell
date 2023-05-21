/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 16:54:17 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/21 16:54:19 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/// @brief Validate the last command in the array of tokens
/// @param tokens The array of tokens (parsed command line)
/// @param i The index of the command in the array to validate
/// @return true if the command is valid, false otherwise
bool	valid_last_command(char **tokens, size_t i)
{
	if (tokens[i][0] == '|' && tokens[i + 1][0] == '>' && !tokens[i + 3])
		return (false);
	return (true);
}

/// @brief Set the has_pipe attribute to 1 for each command in the linked list
/// @param cmds A pointer to the first command in the linked list
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

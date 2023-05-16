/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:30:39 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/09 16:05:22 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Initialize the arguments of a command
/// @param cmd The command
/// @param tokens The tokens array
/// @param start The start index of the command in the tokens array
/// @param end The end index of the command in the tokens array
/// @return The arguments array
/// @note Also handle the redirections arguments
static char	**init_args(t_cmd *cmd, char **tokens, size_t start, size_t end)
{
	char	**args;
	size_t	i;

	args = (char **)malloc((end - start + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
        if (tokens[start + i][0] == '>' || tokens[start + i][0] == '<')
        {
            if (!handle_redirection(tokens, start + i, cmd))
                return (NULL);
            start += 2;
        }
        else
        {
            args[i] = tokens[start + i];
            i++;
        }
	}
	if (i > 0 && args[i - 1][0] == '|')
		i--;
	args[i] = NULL;
	return (args);
}

/// @brief Create a new command from the tokens array
/// @param tokens The tokens array
/// @param start The start index of the command in the tokens array
/// @param end The end index of the command in the tokens array
/// @return The new command
t_cmd	*new_cmd(char **tokens, size_t start, size_t end)
{
	t_cmd	*cmd;
	size_t	i;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->has_heredoc = 0;
	cmd->has_pipe = 0;
	cmd->pid = -1;
	cmd->name = ft_strdup(tokens[start]);
	cmd->args = init_args(cmd, tokens, start, end);
	cmd->next = NULL;
	return (cmd);
}

/// @brief Add a command to the commands linked list
/// @param cmds The commands linked list
/// @param new The command to add
void	add_cmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*last;

	if (new)
	{
		if (!*cmds)
		{
			*cmds = new;
			return ;
		}
		last = *cmds;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

/// @brief Free the commands linked list
/// @param cmds The commands linked list
void	free_cmds(t_cmd *cmds)
{
	t_cmd	*tmp;
	size_t	i;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free(tmp->name);
		i = 0;
		while (tmp->args[i])
			free(tmp->args[i++]);
		free(tmp->args);
		free(tmp);
	}
}

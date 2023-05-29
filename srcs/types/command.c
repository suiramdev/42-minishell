/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:30:39 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/25 23:34:27 by mnouchet         ###   ########.fr       */
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

	args = (char **)ft_calloc(sizeof(char *), end - start + 1);
	if (!args)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		if (tokens[start + i][0] == '>' || tokens[start + i][0] == '<')
		{
			if (!init_redirs(tokens, start + i, cmd))
			{
				while (i > 0)
					free(args[--i]);
				free(args);
				return (NULL);
			}
			start += 2;
			continue ;
		}
		args[i] = ft_strdup(tokens[start + i]);
		i++;
	}
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

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->infile = -1;
	cmd->outfile = -1;
	cmd->has_heredoc = false;
	cmd->has_pipe = false;
	cmd->pid = -1;
	cmd->next = NULL;
	cmd->args = init_args(cmd, tokens, start, end);
	if (!cmd->args || !cmd->args[0])
		return (free_cmds(cmd), NULL);
	cmd->name = cmd->args[0];
	return (cmd);
}

/// @brief Add a command to the commands linked list
/// @param cmds The commands linked list
/// @param new The command to add
void	add_cmd(t_cmd **cmds, t_cmd *new)
{
	t_cmd	*last;

	if (!new)
		return ;
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

/// @brief Get the last argument of the last command
/// @param cmds The commands linked list
char	*last_cmd_arg(t_cmd *cmds)
{
	size_t	i;

	while (cmds->next)
		cmds = cmds->next;
	i = 0;
	while (cmds->args[i])
		i++;
	return (cmds->args[i - 1]);
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
		i = 0;
		while (tmp->args && tmp->args[i])
			free(tmp->args[i++]);
		if (tmp->args)
			free(tmp->args);
		close_redirs(tmp);
		free(tmp);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 14:30:39 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/19 15:38:29 by mnouchet         ###   ########.fr       */
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
	size_t	i;

	cmd->args = (char **)malloc((end - start + 1) * sizeof(char *));
	if (!cmd->args)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		if (tokens[start + i][0] == '>' || tokens[start + i][0] == '<')
		{
			if (!init_redirs(tokens, start + i, cmd))
				return (NULL);
			start += 2;
		}
		else
		{
			cmd->args[i] = ft_strdup(tokens[start + i]);
			i++;
		}
	}
	if (i > 0 && cmd->args[i - 1][0] == '|')
		i--;
	cmd->args[i] = NULL;
	return (cmd->args);
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
	cmd->name = ft_strdup(tokens[start]);
	init_args(cmd, tokens, start, end);
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

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->args)
			free(tmp->args);
		if (tmp->infile > 2)
			close(tmp->infile);
		if (tmp->outfile > 2)
			close(tmp->outfile);
		free(tmp);
	}
}

/// @brief Execute the commands linked list
/// @param cmds The commands linked list
/// @param envs The environment variables linked list
int	exec_cmds(t_cmd *cmds, t_env **envs)
{
	int	backups[2];
	int	exit_status;

	if (cmds->next)
		return (pipeline(cmds, envs));
	backups[0] = dup(STDIN_FILENO);
	backups[1] = dup(STDOUT_FILENO);
	redirs(cmds);
	exit_status = exec_builtin(cmds, envs);
	if (exit_status == BUILTIN_NOT_FOUND)
	{
		cmds->pid = fork();
		if (cmds->pid == -1)
			return (EXIT_FAILURE);
		if (cmds->pid == 0)
			return (exec_relative(cmds, envs));
		close_redirs(cmds);
		dup2(backups[0], STDIN_FILENO);
		dup2(backups[1], STDOUT_FILENO);
		wait_processes(cmds);
		return (EXIT_SUCCESS);
	}
	close_redirs(cmds);
	dup2(backups[0], STDIN_FILENO);
	dup2(backups[1], STDOUT_FILENO);
	return (exit_status);
}

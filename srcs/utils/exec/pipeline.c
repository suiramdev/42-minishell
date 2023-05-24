/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:46:36 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/19 16:33:36 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_pipes(int pipes[2][2])
{
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
}

static int	child_process(size_t index, int pipes[2][2],
	t_cmd *cmd, t_env **envs)
{
	int	builtin_exit;

	if (index > 0)
		dup2(pipes[(index - 1) % 2][0], STDIN_FILENO);
	if (cmd->next)
		dup2(pipes[index % 2][1], STDOUT_FILENO);
	close_pipes(pipes);
	redirs(cmd);
	close_redirs(cmd);
	builtin_exit = exec_builtin(cmd, envs);
	if (builtin_exit == BUILTIN_NOT_FOUND)
		return (exec_relative(cmd, envs));
	return (builtin_exit);
}

/// @brief Waits for all the processes to finish
/// @param cmds The commands to execute
void	wait_processes(t_cmd *cmds, t_env **envs)
{
	int		status;

	status = 0;
	while (cmds)
	{
		waitpid(cmds->pid, &status, 0);
		set_env(envs, "?", ft_itoa(WEXITSTATUS(status)));
		cmds = cmds->next;
	}
}

bool	is_child_process(t_cmd *cmds)
{
	while (cmds)
	{
		if (cmds->pid == 0)
			return (true);
		cmds = cmds->next;
	}
	return (false);
}

/// @brief Executes the commands in a pipeline
/// @param cmds The commands to execute
/// @param envs The environment variables
/// @return EXIT_SUCCESS, EXIT_FAILURE, or the exit code of the command
int	pipeline(t_cmd *cmds, t_env **envs)
{
	t_cmd	*cmd;
	size_t	i;
	int		pipes[2][2];

	cmd = cmds;
	i = 0;
	if (pipe(pipes[1]) == -1)
		return (EXIT_FAILURE);
	while (cmd)
	{
		if (pipe(pipes[i % 2]) == -1)
			return (EXIT_FAILURE);
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (EXIT_FAILURE);
		if (cmd->pid == 0)
			return (child_process(i, pipes, cmd, envs));
		if (i > 0)
			close(pipes[(i - 1) % 2][0]);
		close(pipes[i % 2][1]);
		i++;
		cmd = cmd->next;
	}
	wait_processes(cmds, envs);
	close(pipes[i % 2][0]);
	return (EXIT_SUCCESS);
}

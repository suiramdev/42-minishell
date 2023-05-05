/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:50:53 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/05 14:52:08 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "utils/path.h"
#include "builtins.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Should be replaced, this is just for testing
static void	close_pipes(int pipes[2][2])
{
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
}

static int	child_process(size_t index, int pipes[2][2],
	t_cmd *cmd, t_env *envs)
{
	char	*path;
	char	**envp;
	size_t	i;

	if (index > 0)
		dup2(pipes[(index - 1) % 2][0], STDIN_FILENO);
	if (cmd->next)
		dup2(pipes[index % 2][1], STDOUT_FILENO);
	close_pipes(pipes);
	if (builtins(cmd, envs) == EXIT_FAILURE)
	{
		path = resolve_path(cmd->name, envs);
		envp = format_env(envs);
		execve(path, cmd->args, envp);
		free(path);
		i = 0;
		while (envp[i])
			free(envp[i++]);
		free(envp);
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd->name, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/// @brief Execute a list of commands in parallel processes
/// @param cmds The list of commands to execute
/// @return The exit status of the command or the main process
int	exec_cmds(t_cmd *cmds, t_env *envs)
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
		if (cmd->next)
			close(pipes[i % 2][1]);
		i++;
		cmd = cmd->next;
	}
	cmd = cmds;
	while (cmd)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
	close_pipes(pipes);
	return (EXIT_SUCCESS);
}

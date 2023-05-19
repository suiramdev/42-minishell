/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:50:53 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/08 17:11:17 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"
#include "minishell.h"
#include <stdlib.h>

// Should be replaced, this is just for testing
static void	close_pipes(int pipes[2][2])
{
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
}

static int	builtins_exec(t_cmd *cmd, t_env **envs)
{
	t_builtin	builtins[7];
	size_t		i;

	builtins[0] = (t_builtin){.name = "cd", .func = builtin_cd};
	builtins[1] = (t_builtin){.name = "echo", .func = builtin_echo};
	builtins[2] = (t_builtin){.name = "env", .func = builtin_env};
	builtins[3] = (t_builtin){.name = "exit", .func = builtin_exit};
	builtins[4] = (t_builtin){.name = "export", .func = builtin_export};
	builtins[5] = (t_builtin){.name = "pwd", .func = builtin_pwd};
	builtins[6] = (t_builtin){.name = "unset", .func = builtin_unset};
	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(builtins[i].name, cmd->name) == 0)
		{
			return (builtins[i].func(cmd, envs));
		}
		i++;
	}
	return (BUILTIN_NOT_FOUND);
}

static int	default_exec(t_cmd *cmd, t_env **envs)
{
	char	*path;
	char	**envp;
	size_t	i;

	path = resolve_path(cmd->name, *envs);
	envp = format_env(*envs);
	execve(path, cmd->args, envp);
	free(path);
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	ft_errorendl("Command not found: ", cmd->name);
	return (EXIT_FAILURE);
}

static int	child_process(size_t index, int pipes[2][2],
	t_cmd *cmd, t_env **envs)
{
	if (index > 0)
		dup2(pipes[(index - 1) % 2][0], STDIN_FILENO);
	if (cmd->next)
		dup2(pipes[index % 2][1], STDOUT_FILENO);
	close_pipes(pipes);
	if (builtins_exec(cmd, envs) == BUILTIN_NOT_FOUND)
		return (default_exec(cmd, envs));
	return (EXIT_SUCCESS);
}

static int	piped_exec(t_cmd *cmds, t_env **envs)
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
		if (pipe(pipes[i % 2]) == -1) // We should close the pipes
			return (EXIT_FAILURE);
		cmd->pid = fork();
		if (cmd->pid == -1) // We should close the pipes
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

/// @brief Executes commands
/// @param cmds The commands to execute
/// @param envs The environment variables
/// @return EXIT_SUCCESS or EXIT_FAILURE if an error occured
int	exec(t_cmd *cmds, t_env **envs)
{
	int	exit_status;

	if (cmds->next)
		return (piped_exec(cmds, envs));
	exit_status = builtins_exec(cmds, envs);
	if (exit_status == BUILTIN_NOT_FOUND)
	{
		cmds->pid = fork();
		if (cmds->pid == -1)
			return (EXIT_FAILURE);
		if (cmds->pid == 0)
			return (default_exec(cmds, envs));
		waitpid(cmds->pid, NULL, 0);
	}
	return (exit_status);
}

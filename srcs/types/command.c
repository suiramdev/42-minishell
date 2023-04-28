/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */ /*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:28:40 by mnouchet          #+#    #+#             */
/*   Updated: 2023/04/27 15:31:52 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types/command.h"
#include "builtins.h"
#include "libft.h"
#include "utils/path.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/// @brief Create new commands for testing purposes
/// @param env The environment variables linked list
/// @return The list of commands, or NULL if an error occurred
/// @note This function is temporary, it will be replaced by the parser.
/// It may contain memory leaks, it is not intended to be used in production
t_cmd	*example_cmds(t_env *env)
{
	t_cmd		*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = "cat";
	cmd->args = NULL;
	cmd->env = env;
	cmd->next = NULL;
	return (cmd);
}

// Should be replaced, this is just for testing
static void	close_pipes(int pipes[2][2])
{
	close(pipes[0][0]);
	close(pipes[0][1]);
	close(pipes[1][0]);
	close(pipes[1][1]);
}

static int	child_process(size_t index, int pipes[2][2], t_cmd *cmd)
{
	char	*path;
	char	**envp;
	size_t	i;

	if (index > 0)
		dup2(pipes[(index - 1) % 2][0], STDIN_FILENO);
	if (cmd->next)
		dup2(pipes[index % 2][1], STDOUT_FILENO);
	close_pipes(pipes);
	if (builtins(cmd) == EXIT_FAILURE)
	{
		path = resolve_path(cmd->name, cmd->env);
		printf("path: %s\n", path);
		envp = format_env(cmd->env);
		execve(path, cmd->args, envp);
		free(path);
		i = 0;
		while (envp[i])
			free(envp[i++]);
		free(envp);
		ft_putstr_fd("Command not found: ", STDERR_FILENO);
		ft_putstr_fd(cmd->name, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO); // Maybe use putsr endl
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/// @brief Execute a list of commands in parallel processes
/// @param cmds The list of commands to execute
/// @return EXIT_SUCCESS if the command was executed successfully
/// EXIT_FAILURE otherwise
int	exec_cmds(t_cmd *cmds)
{
	t_cmd	*cmd;
	size_t	i;
	int		pipes[2][2];

	cmd = cmds;
	i = 0;
	while (cmd)
	{
		if (pipe(pipes[i % 2]) == -1)
			return (EXIT_FAILURE);
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (EXIT_FAILURE);
		if (cmd->pid == 0)
			child_process(i, pipes, cmd);
		close_pipes(pipes);
		i++;
		cmd = cmd->next;
	}
	cmd = cmds;
	while (cmd)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
	return (EXIT_SUCCESS);
}

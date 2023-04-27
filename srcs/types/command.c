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
	cmd->name = "cd";
	cmd->args = malloc(sizeof(char *) * 3);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->args[0] = "cd";
	cmd->args[1] = "dddd";
	cmd->args[2] = NULL;
	cmd->env = env;
	cmd->next = malloc(sizeof(t_cmd));
	if (!cmd->next)
	{
		free(cmd->args);
		free(cmd);
		return (NULL);
	}
	cmd->next->name = "pwd";
	cmd->next->args = malloc(sizeof(char *) * 2);
	if (!cmd->next->args)
	{
		free(cmd->next);
		free(cmd->args);
		free(cmd);
		return (NULL);
	}
	cmd->next->args[0] = "pwd";
	cmd->next->args[1] = NULL;
	cmd->next->env = env;
	cmd->next->next = NULL;
	return (cmd);
}

static int	child_process(t_cmd *cmd)
{
	char	*path;

	if (builtins(cmd) == EXIT_FAILURE)
	{
		path = resolve_path(cmd->name, cmd->env);
		execve(path, cmd->args, format_env(cmd->env));
		printf("Command not found: %s\n", cmd->name);
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

	cmd = cmds;
	while (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (EXIT_FAILURE);
		if (cmd->pid == 0)
			child_process(cmd);
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

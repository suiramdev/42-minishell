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
#include "utils/parsing.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

t_cmd	*last_cmd(t_cmd *cmds)
{
	while (cmds->next)
		cmds = cmds->next;
	return (cmds);
}

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
		last = last_cmd(*cmds);
		last->next = new;
	}
}

t_cmd	*new_cmd(char **tokens, int start, int end)
{
    t_cmd	*cmd;
    int		i;

    i = 0;
    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return 0;
    cmd->args = (char **)malloc((end - start + 1) * sizeof(char *));
    if (!cmd->args)
        return 0;
    while (start + i < end)
    {
        cmd->args[i] = tokens[start + i];
        i++;
    }
    cmd->args[i] = 0;
    cmd->next = 0;
    return (cmd);
}

t_cmd	*init_cmds(char **tokens)
{
    t_cmd	*cmds;
    t_cmd	*new;
    int		start;
    int		i;

    cmds = NULL;
    start = 0;
    i = 0;
    while (tokens[i])
    {
        // If there is a pipe
        if (has_pipes(tokens[i]))
        {
            // Create a node with args[start] to args[i]
            new = new_cmd(tokens, start, i);
            add_cmd(&cmds, new);
            // Jump the pipe
            start = i + 1;
        }
        i++;
    }
    // Create node from 0 to end if no pipe
    // Or create last node from pipe to end if pipe
    new = new_cmd(tokens, start, i);
    add_cmd(&cmds, new);
    return (cmds);
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
	if (pipe(pipes[0]) == -1 || pipe(pipes[1]) == -1)
		return (EXIT_FAILURE);
	while (cmd)
	{
		if (i > 0 && pipe(pipes[i % 2]) == -1)
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

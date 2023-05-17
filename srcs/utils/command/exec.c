/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:46:34 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/17 10:05:03 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Executes a builtin command
/// @param cmd The command to execute
/// @param envs The environment variables
/// @return BUILTIN_NOT_FOUND, or the exit code of the command
int	exec_builtin(t_cmd *cmd, t_env **envs)
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
			return (builtins[i].func(cmd, envs));
		i++;
	}
	return (BUILTIN_NOT_FOUND);
}

/// @brief Executes a command relative to the current directory or environment
/// variables
/// @param cmd The command to execute
/// @param envs The environment variables
/// @return EXIT_SUCCESS, EXIT_FAILURE, or the exit code of the command
int	exec_relative(t_cmd *cmd, t_env **envs)
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
	ft_putstr_fd("Command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd->name, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (EXIT_FAILURE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 00:46:34 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/26 02:02:26 by mnouchet         ###   ########.fr       */
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
	struct stat sb;
	char	*path;
	char	**envp;
	size_t	i;

	path = resolve_path(cmd->name, *envs, F_OK);
	if (!path)
		return (error(cmd->name, "command not found"), 127);
	lstat(path, &sb);
	if (S_ISDIR(sb.st_mode))
		return (error(path, "Is a directory"), 126);
	envp = format_env(*envs);
	execve(path, cmd->args, envp);
	free(path);
	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
	return (EXIT_FAILURE);
}

/// @brief Execute the commands linked list
/// @param cmds The commands linked list
/// @param envs The environment variables linked list
int	exec_cmds(t_cmd *cmds, t_env **envs)
{
	int		backups[2];
	int		exit_status;

	signal(SIGINT, &cmd_signal);
	signal(SIGQUIT, &cmd_signal);
	if (cmds->next)
		return (pipeline(cmds, envs));
	backups[0] = dup(STDIN_FILENO);
	backups[1] = dup(STDOUT_FILENO);
	redirs(cmds);
	exit_status = exec_builtin(cmds, envs);
	dup2(backups[0], STDIN_FILENO);
	dup2(backups[1], STDOUT_FILENO);
	close(backups[0]);
	close(backups[1]);
	if (exit_status == BUILTIN_NOT_FOUND)
		return (pipeline(cmds, envs));
	set_env(envs, "?", ft_itoa(exit_status));
	close_redirs(cmds);
	return (exit_status);
}

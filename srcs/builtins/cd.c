/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:58:49 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/29 18:57:33 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_invalid(char *path)
{
	struct stat	sb;

	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	if (stat(path, &sb) == -1)
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	else if (!S_ISDIR(sb.st_mode))
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	else
		ft_putstr_fd(": Unknown error\n", STDERR_FILENO);
}

static char	*arg_path(t_cmd *cmd)
{
	size_t	i;
	size_t	count;
	char	*path;

	i = 1;
	count = 0;
	path = NULL;
	while (cmd->args[i])
	{
		if (cmd->args[i][0])
		{
			path = cmd->args[i];
			count++;
		}
		i++;
	}
	if (count > 1)
		return (error("cd", "too many arguments"), NULL);
	return (path);
}

static char	*home_path(t_env **envs)
{
	t_env	*env;

	env = get_env(*envs, "HOME");
	if (!env)
		return (error("cd", "HOME not set"), NULL);
	return (env->value);
}

/// @brief Execute the cd builtin command
/// @param cmd The command data structure
/// @param envs The environment variables
/// @return EXIT_SUCCESS or EXIT_FAILURE if an error occured
int	builtin_cd(t_cmd *cmd, t_env **envs)
{
	char		*path;
	char		current[1024];

	path = arg_path(cmd);
	if (!path)
		path = home_path(envs);
	if (!path)
		return (EXIT_FAILURE);
	if (path[0])
	{
		if (chdir(path) == -1)
			return (error_invalid(path), EXIT_FAILURE);
		if (getcwd(current, 1024))
			set_env(envs, "PWD", ft_strdup(current));
	}
	return (EXIT_SUCCESS);
}

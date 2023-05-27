/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnouchet <mnouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:58:49 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/26 00:31:23 by mnouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Execute the cd builtin command
/// @param cmd The command data structure
/// @param envs The environment variables
/// @return EXIT_SUCCESS or EXIT_FAILURE if an error occured
int	builtin_cd(t_cmd *cmd, t_env **envs)
{
	t_env	*env;
	char	*path;

	if (cmd->args[1])
	{
		if (cmd->args[2])
			return (error("cd", "too many arguments"), EXIT_FAILURE);
		path = cmd->args[1];
	}
	else
	{
		env = get_env(*envs, "HOME");
		if (!env)
			return (error("cd", "HOME not set"), EXIT_FAILURE);
		path = env->value;
	}
	if (chdir(path) == -1)
		return (perror("cd"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zdevove <zdevove@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:01:31 by mnouchet          #+#    #+#             */
/*   Updated: 2023/05/30 15:36:16 by zdevove          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/// @brief Execute the env builtin command
/// @param cmd The command data structure
/// @param envs The environment variables
/// @return EXIT_SUCCESS, EXIT_FAILURE if an error occured
int	builtin_env(t_cmd *cmd, t_env **envs)
{
	t_env	*env;

	(void)cmd;
	env = *envs;
	while (env)
	{
		if (env->value)
		{
			if (printf("%s=%s\n", env->key, env->value) < 0)
				return (error_write("env"), EXIT_FAILURE);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
